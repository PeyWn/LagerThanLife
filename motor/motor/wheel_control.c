#include    "wheel_control.h"
#include    "math.h"

/* lokal constants */
#define     TURN_MAX    0.7f    // turn speed +/-7 => TURN_MAX higher/lower PWM
#define     MOTOR_MAX   0.9f    // physical max setting for PWM. don't use 100%

/* variables for using timer in testing */
unsigned    int period_counter  = 0;
unsigned    int second_counter  = 0;
            int has_counted     = 0;
            
/* base speed of PWM, only changes when turning or stopping, set in init_wheel_control */
float   PWM_duty_ratio;     // base speed; set with "init_wheel_control"
int     traversal_status;   // current setting for fwd/backwd movement
int     turn_status;        // current setting for left/right turn

/* timer for waiting (8MHz setting) ------------------------------------------------*/
int seconds(unsigned int seconds)
{
     if ( TCNT0 > 200 && !(has_counted)){
         has_counted = 1;
         period_counter += 1;
     }
     else if ( TCNT0 < 200 ){
         has_counted = 0;
     }
     if ( period_counter >= 15770 ){ // 15770Hz is measured in oscilloscope (8Mhz)
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
/*----------------------------------------------------------------------------------*/

int init_wheel_control(float base_speed)
{   
    /* set OC0A and OC0B on compare match when up-counting, clear on down-counting */ 
    TCCR0A |= 1<<COM0A1 | 1<<COM0A0 | 1<<COM0B1 | 1<<COM0B0;
    
    /* Phase correct PWM */ 
    TCCR0A |=     1<<WGM00;
    TCCR0A &=   ~(1<<WGM01);
    TCCR0B &=   ~(1<<WGM02);
    
    /* clk source, no prescaling for 8Mhz. (divide by 2 for 16Mhz) */
    TCCR0B |=   1<<CS00;
    TCCR0B &= ~(1<<CS02 |1<<CS01);

    /* enable interupt for compare match A and B on timer TCNT0 */
    TIMSK0 |= (1<<OCIE0B)|(1<<OCIE0A);
    
    /* set PB3, PB4 as output for PB4, PB5, PC1, PC0 */
    DDRB  |= (1<<DDB4) | (1<<DDB3); //PWM
    DDRC  |= (1<<DDC1) | (1<<DDC0); //DIR1

    /* set initial variable values, speed and turn to 0 */
    PWM_duty_ratio = base_speed > MOTOR_MAX ? MOTOR_MAX : base_speed;
    set_traversal_speed(0);
    set_turn_speed(0);
    
    return 0;
}

/*  local function:
    compute and set PWM on pins for PWM based on new turn
    setting and on current traversal status. Completely
    copied from design specification. Also sets DIR1 and
    DIR2 pins. Rotation is based on current traversal speed 
    such that the robot will maintain same traversal 
    movement when rotating. The rotation is scaled by the 
    TURN_MAX constant and restricted by the MOTOR_MAX constant.
    
    arg int turn_value:
    new setting for turn speed (see constants at top of
    document. Positive is left. Use turn_status to keep
    old value.
    
    arg int trav_value:
    new setting for traversal value. use traversal_satus
    to keep old value.
    
    no returned value:
    result is setting the OCR0A and OCR0B to correct values
    as well as setting the pins for DIR1 and DIR2;
*/
void set_PWM(int turn_value, int trav_value)
{
    /* PWM speed variables */
    float turn    =  turn_value * TURN_MAX/7;       // turn direciton
    float left    =  trav_value * PWM_duty_ratio;   // left motors' speed
    float right   =  trav_value * PWM_duty_ratio;   // right motors' speed
    
    /* Compensate opposite motor if turn results in too big PWM duty */
    if (left + turn > MOTOR_MAX){
        right = right - (left + turn - MOTOR_MAX);
        left  = MOTOR_MAX;
    }else if(left + turn < -MOTOR_MAX){
        right = right + (left + turn + MOTOR_MAX);
        left  = -MOTOR_MAX;
    }else if(right - turn > MOTOR_MAX){
        left  = left - (right - turn - MOTOR_MAX);
        right = MOTOR_MAX;
    }else if(right - turn < -MOTOR_MAX){
        left  = left + (right - turn + MOTOR_MAX);
        right = MOTOR_MAX;
    }
    /* if within limitations just add turn value */
    else{  
        left = left + turn;
        right = right - turn;
    }
    
    /* set PWM duty */
    OCR0A = (int)(255 * ( 1 - fabs(left) ) );
    OCR0B = (int)(255 * ( 1 - fabs(right)) );
    
    /* set direction on left wheel side */
    if(left < 0){
        PORTC |= 1<<PORTC0;
    }else{
        PORTC &= ~(1<<PORTC0);
    }
    
    /* set direction on right wheel side */
    if(right < 0){
        PORTC &= ~(1<<PORTC1);
    }else{
        PORTC |= 1<<PORTC1;
    }
}

/*  function:
    set a new speed for moving robot forward/backward or stop.
    Front of robot is based on where sensors are placed
    (2017-11-05).
    
    arg int trav_value :
    the new traversal value for moving the robot forward and
    backward. Set only to values:
    1  - forward
    0  - stop
    -1 - backward
    */
void set_traversal_speed(int trav_value)
{
    set_PWM(turn_status, trav_value); 
    traversal_status = trav_value;
}

/*  function:
    set new turning speed for robot rotation. Rotation is
    based on current traversal speed such that the robot will
    maintain same traversal movement when rotating. The rotation
    is scaled by the TURN_MAX constant and restricted by the
    MOTOR_MAX constant.
    
    arg int turn_value:
    the new turn speed setting. Can be set to any integer 
    value in the interval +/-7 where positive is right turn
    and 0 is no turning.
*/
void set_turn_speed(int turn_value)
{
    set_PWM(turn_value, traversal_status);
    turn_status = turn_value;
}    
 
void update_wheel_control(){
    
    /* wait 1 sec before starting */
    while(!seconds(1));
    
    /* backwd left turn 2 sec */
    set_traversal_speed(-1);
    set_turn_speed(-2);
    while(!seconds(2));
    
    /* stop */
    set_traversal_speed(0);
    set_turn_speed(0);
}
 