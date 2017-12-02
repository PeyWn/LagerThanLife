#include    "wheel_control.h"
#include    "math.h"

/* physical limitations (do not change)                                                         */
#define MOTOR_MAX       0.95f   // physical max PWM for DC-motors
#define TURN_MIN        0.285f  // physical min PWM for turning when still
#define TURN_MIN_MOVING 0.143f  // physical min PWM for turning while moving

/*  DEFAULT PARAMETERS FOR SPEED - MAX SPEEDS:
    Max speeds of turn and traversal movement. The current speeds are scaled by this factor. PWM
    output is restricted from above by MOTOR_MAX. TURN_MIN and TURN_MIN_MOVING corresponds to
    the lowest turn speed setting 1 with no traversal speed and with traversal speed
    respectively. When turn speed is greater than traversal speed, the slower wheel will switch
    direction.                                                                                  */
double trav_max = 0.85f;   // ratio of MOTOR_MAX;
double turn_max = 0.70f;   // ratio of MOTOR_MAX;

/* current speeds */
int trav_status = 0;        // current traversal speed -MAX_TRAV_SETTING ... +MAX_TRAV_SETTING
int turn_status = 0;        // current turn speed      -MAX_TURN_SETTING ... +MAX_TURN_SETTING

/*-----------------------------------locally used functions-------------------------------------*/

/*  set output correctly and safely using the OCR0A and OCR0B as PWM-signals.

    arg double left:
    percentage of PWM for left wheel-side

    arg double right:
    percentage of PWM for right whell-side                                                      */
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

/*  Set both wheel-sides' speed by scaling the set parameters turn_max and trav_max with the
    turn_speed and trav_speed given as arguments respectively.

    arg int turn_speed:
    an integer value between +/- MAX_TURN_SETTING

    arg int trav_speed:
    an integer value between +/- MAX_TRAV_SETTING                                               */
void set_wheel_speeds(int turn_setting, int trav_setting)
{
    volatile double     turn_speed = turn_setting;
    volatile double     trav_speed = trav_setting;

    volatile double     left,       right,      trav_scale,
                        turn_max,   turn_min,
                        diff,       diff_R,     diff_L;

    volatile int        sign_L;
    volatile int        sign_R;

    volatile double turn_dir   = turn_speed < 0? -1 : 1;
    volatile double trav_dir   = trav_speed < 0? -1 : 1;

    /* map traversal speed to PWM value */
    trav_scale = trav_param * MOTOR_MAX;
    trav_speed = ((float)trav_speed/MAX_TRAV_SETTING) * trav_scale;


    /* map turn speed to PWM value */
    if(turn_speed != 0){ //not divide by 0
        turn_max   = turn_param   * MOTOR_MAX;                                  // max PWM-value
        turn_min   = fabs(trav_speed) > 0 ? TURN_MIN_MOVING : TURN_MIN;         // decrease lower bound (turn) if moving
        turn_speed = turn_dir   * ((fabs(turn_speed)-1) / MAX_TURN_SETTING);    // map to zero-index
        turn_speed = turn_speed * (turn_max - turn_min) + turn_min*turn_dir;    // scale by max + minimum
    }

    /* wanted speeds */
    left  = trav_speed + turn_speed;
    right = trav_speed - turn_speed;

    /* compensate right/left if breach MOTOR_MAX */
	if(fabs(trav_speed) > 0){
		sign_L  = left  < 0 ? -1 : 1;
		sign_R  = right < 0 ? -1 : 1;
		diff_L  = (fabs(left)  - MOTOR_MAX);
		diff_R  = (fabs(right) - MOTOR_MAX);
		diff    =  (diff_L>0)*(sign_L*diff_L) + (diff_R>0)*(sign_R*diff_R);
		left    =  left  - diff*trav_dir;
		right   =  right - diff*trav_dir;
	}

    /* final output */
    set_PWM(left, right);
}

/*------------------------------------publicly used functions-----------------------------------*/

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
