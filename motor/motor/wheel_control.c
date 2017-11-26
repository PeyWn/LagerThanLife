#include    "wheel_control.h"
#include    "math.h"

/* physical limitations (by test) */
#define MOTOR_MAX 0.95f  // physical max PWM for DC-motors
#define TURN_MIN  0.285f // physical min PWM for turning

/* parameters for speed */
double trav_param = 0.5f;   // ratio MOTOR_MAX; safe:0.3
double turn_param = 1.0f;   // ratio trav_speed; safe-limit:1.0; more->direction-change

/* current speeds */
int trav_status = 0;        // current traversal speed -MAX_TRAV_SETTING ... +MAX_TRAV_SETTING
int turn_status = 0;        // current turn speed      -MAX_TURN_SETTING ... +MAX_TURN_SETTING

/* variables for using timer in testing */
unsigned    int period_counter  = 0;
unsigned    int second_counter  = 0;
            int has_counted     = 0;

/*--------------------locally used functions----------------------*/

/* timer for waiting (set for 16MHz 8-bit timer with 8x clock divide)
   starts counting seconds from 0 when called upon. It must
   be called once every timer-period in order to update. It
   is reset if called and the amount of seconds has passed.
    
   arg int seconds:
   amount of seconds to wait.
   
   return (int bool):
   return true if the amount of seconds has passed since
   first call to funtion, false otherwise.
*/
int seconds(unsigned int seconds)
{
     if ( TCNT0 > 200 && !(has_counted)){
         has_counted = 1;
         period_counter += 1;
     }
     else if ( TCNT0 < 200 ){
         has_counted = 0;
     }
     
     /* 15.770kHz is measured in oscilloscope           (8Mhz) 
        16Mhz and timer-clock-divide 8 => approx 4kHz   (16MHz)
     */
     if ( period_counter >= 4000 ){ 
         second_counter += 1;
         period_counter = 0;
     }
     if (second_counter > seconds){
         second_counter = 0;
         return 1;
     }
     else
     {
         return 0;
     }
}

/*  set output correctly and safely.

    arg double left:
    percentage of PWM for left wheel-side
    
    arg double right:
    percentage of PWM for right whell-side          */
void set_PWM(double left, double right){
    
    /* safety net */
    if(fabs(left) > MOTOR_MAX){
        left  = MOTOR_MAX * left  / fabs(left);
    }
    if(fabs(right) > MOTOR_MAX){
        right = MOTOR_MAX * right / fabs(right);
    }
    
    /* set PWM duty - 255 is increments of the timer */
    OCR0A = (int)(255 * ( 1 - fabs(right) ) );
    OCR0B = (int)(255 * ( 1 - fabs(left)  ) );
    
    /* set direction on left wheel side */
    if(right >= 0){
        PORTC &= ~(1<<PORTC0);
    }
    else{
        PORTC |= 1<<PORTC0;
    }
    
    /* set direction on right wheel side */
    if(left >= 0){
        PORTC |= 1<<PORTC1;
    }
    else{
        PORTC &= ~(1<<PORTC1);
    }
}

/*  Set both wheel-sides' speed by scaling the set parameters
    with the turn_speed and trav_speed given as arguments.
    Turn-speed scales with current trav-speed if the robot
    is moving. This is because 1.0 turn_param should result
    in no switch of DC-motor direction when moving forward.
    The safety for restricting speed to MOTOR_MAX is given by
    the function set_PWM and is recommended for setting speeds
    of both wheel-sides.
    
    arg int turn_speed:
    an integer value between +/- MAX_TURN_SETTING
    
    arg int trav_speed:
    an integer value between +/- MAX_TRAV_SETTING
*/
void set_wheel_speeds(int turn_setting, int trav_setting)
{
    volatile double     left, right, trav_scale, turn_scale, diff, diff_R, diff_L, turn_dir;
    volatile double     turn_speed = turn_setting;
    volatile double     trav_speed = trav_setting;
                        
    volatile int        negative_L;
    volatile int        negative_R;

    /* map traversal speed to PWM value */
    trav_scale = trav_param * MOTOR_MAX;
    trav_speed = (trav_speed/MAX_TRAV_SETTING) * trav_scale;

    /* map turn speed to PWM value, scale by trav_speed */
    if(trav_speed == 0){
        turn_scale = turn_param * (trav_scale - TURN_MIN);
    }
    else{
        turn_scale = turn_param * (trav_speed - TURN_MIN);
    }
    if(turn_speed != 0){
        turn_dir = turn_speed/fabs(turn_speed);
        turn_speed = ( (fabs(turn_speed)-1)/MAX_TURN_SETTING );
        turn_speed = (turn_scale * (fabs(turn_speed)) + TURN_MIN) * turn_dir;
        //turn_speed = (fabs(turn_speed) - 1) *(turn_scale - TURN_MIN) + TURN_MIN;
        //turn_speed = turn_speed * turn_speed / fabs(turn_speed);
    }

    /* resulting wheel speeds */
    left  = trav_speed + turn_speed;
    right = trav_speed - turn_speed;
    negative_L = left  < 0 ? -1 : 1;
    negative_R = right < 0 ? -1 : 1;

    /* compensate right/left if breach MOTOR_MAX */
    diff_L  = (fabs(left)  - MOTOR_MAX);
    diff_R  = (fabs(right) - MOTOR_MAX);
    diff    =  negative_L*diff_L*(diff_L>0) - negative_R*diff_R*(diff_R>0);
    left    =  left  - diff;
    right   =  right + diff;

    /* final output */
    set_PWM(left, right);
}
/*----------------------------------------------------------------*/

/*---------------------publicly used functions--------------------*/

int init_wheel_control()
{   
    /* set OC0A and OC0B on compare match when up-counting, clear on down-counting */ 
    TCCR0A |= 1<<COM0A1 | 1<<COM0A0 | 1<<COM0B1 | 1<<COM0B0;
    
    /* Phase correct PWM */ 
    TCCR0A |=     1<<WGM00;
    TCCR0A &=   ~(1<<WGM01);
    TCCR0B &=   ~(1<<WGM02);
    
    /* clk source, no prescaling for 8Mhz. (divide by 8 for 16MHz -> 2 MHz) */
    TCCR0B &= ~(1<<CS00);
    TCCR0B |=  (1<<CS01);
    TCCR0B &= ~(1<<CS02);

    /* enable interupt for compare match A and B on timer TCNT0 */
    TIMSK0 |= (1<<OCIE0B)|(1<<OCIE0A);
    
    /* set initial variable values, speed and turn to 0 */
    set_traversal_speed(0);
    set_turn_speed(0);
    
    /* set PB3, PB4 as output for PB4, PB5, PC1, PC0 */
    DDRB  |= (1<<DDB4) | (1<<DDB3); //PWM
    DDRC  |= (1<<DDC1) | (1<<DDC0); //DIR1
    
    return 0;
}

int get_traversal_status(){
    return trav_status;
}

int get_turn_status(){
    return turn_status;
}

void set_traversal_param(double trav_value){
    trav_param = trav_value;
}

void set_turn_param(double turn_value){
    turn_param = turn_value;
}

void set_traversal_speed(int trav_value)
{
    if(fabs(trav_value) > MAX_TRAV_SETTING){
        trav_value = trav_value/fabs(trav_value)*MAX_TRAV_SETTING;
    }
    set_wheel_speeds(turn_status, trav_value); 
    trav_status = trav_value;
}

void set_turn_speed(int turn_value)
{
    if(fabs(turn_value) > MAX_TURN_SETTING){
        turn_value = turn_value/fabs(turn_value)*MAX_TURN_SETTING;
    }
    set_wheel_speeds(turn_value, trav_status);
    turn_status = turn_value;
}
 
void update_wheel_control(){
    
}
 