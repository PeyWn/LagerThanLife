#include    "wheel_control.h"
#include    "stdlib.h"

/* LOKAL CONSTANTS */
#define     TURN_MAX    0.3f    // turn speed +/-7 => TURN_MAX higher/lower PWM
#define     MOTOR_MAX   1       // physical max setting for PWM 

//variables for using timer in testing
unsigned    int period_counter  = 0;
unsigned    int second_counter  = 0;
            int has_counted     = 0;
            
//base speed of PWM, only changes when turning or stopping, set in init_wheel_control
float   PWM_duty_ratio  =   0;      // base speed; set with "init_wheel_control"
int     traversal_status;   // current setting for fwd/backwd movement
int     turn_status;        // current setting for left/right turn

/*
     todo:
     . 16MHz/8MHz setup
     . turn
     . initial speed
     . action on command
 */

/* UTILITY wheel_control.c  --------------------------------------------------------*/
int seconds(unsigned int seconds){
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
    PWM_duty_ratio = base_speed; //set both wheel sides to 0
    
    //set OC0A and OC0B on compare match when up-counting, clear on down-counting
    TCCR0A |= 1<<COM0A1 | 1<<COM0A0 | 1<<COM0B1 | 1<<COM0B0;
    
    //Phase correct PWM
    TCCR0A |=     1<<WGM00;
    TCCR0A &=   ~(1<<WGM01);
    TCCR0B &=   ~(1<<WGM02);
    
    //clk source, no prescaling for 8Mhz. (divide by 2 for 16Mhz)
    TCCR0B |=   1<<CS00;
    TCCR0B &= ~(1<<CS02 |1<<CS01);

    // enable interupt for compare match A and B on timer TCNT0
    TIMSK0 |= (1<<OCIE0B)|(1<<OCIE0A);
    
    //set PB3, PB4 as output for PB4, PB5, PC1, PC0
    DDRB  |= (1<<DDB4) | (1<<DDB3); //PWM
    DDRC  |= (1<<DDC1) | (1<<DDC0); //DIR1

    set_traversal_speed(0); // initial speed 0
    return 0;
}

/*  local function:
    set pin outputs for DIR1 and DIR2
    
    arg int dir:
    dir shall be assigned one of the values for direction
    (see CONSTANTS at top of document)                         */
/*
void set_dir_pins(int dir)
{
    switch(dir){
        case RIGHT:     // direction tested
            PORTC |=  (1<<PORTC0);
            PORTC |=  (1<<PORTC1);
        break;
        case LEFT:      // direction tested
            PORTC &= ~(1<<PORTC0);
            PORTC &= ~(1<<PORTC1);
        break;
        case FWD:       // direction tested
            PORTC &= ~(1<<PORTC0);
            PORTC |=  (1<<PORTC1);
        break;
        case BACKWD:    // direction tested
            PORTC |=  (1<<PORTC0);
            PORTC &= ~(1<<PORTC1);
        break;
    }
}
*/


/*  local function:
    compute and set PWM on pins for PWM based on new turn
    setting and on current traversal status. Completely
    copied from design specification.
    
    arg int turn_value:
    new setting for turn speed (see constants at top of
    document. Positive is left.
    
    no returned value:
    result is setting the OCR0A and OCR0B to correct values
    as well as setting the pins for DIR1 and DIR2;
*/
void set_turn_speed(int turn_value){
    // PWM speed variables
    float turn    =  turn_value * TURN_MAX/7;
    float left    =  traversal_status * PWM_duty_ratio;
    float right   = -traversal_status * PWM_duty_ratio;
    
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
    }else{  // if within limitations just add turn value
        left = left + turn;
        right = right - turn;
    }
    
    // set PWM duty
    OCR0A = abs(left);
    OCR0B = abs(right);
    
    // set direction on left wheel side
    if(left < 0){
        PORTC &= ~(1<<PORTC0);
    }else{
        PORTC |= 1<<PORTC0;
    }
    
    // set direction on right wheel side
    if(right > 0){
        PORTC |= 1<<PORTC1;
    }else{
        PORTC &= ~(1<<PORTC1);
    }
    
    // update current turn setting
    turn_status = turn_value;
}

/*  function:
    update traversal status and compute PWM with turn function
    based on current status.                                    */
void set_traversal_speed(int trav_value){
    traversal_status = trav_value;
    set_turn_speed(turn_status); 
}

/*
void set_traversal_speed(int trav_value){
    
    //max(TCNT0)=255
    int downtime = 255 - PWM_duty_ratio*255;
    
    switch(trav_value){
        case FWD:     // set forward speed
            set_dir_pins(FWD);
            OCR0A = downtime;
            OCR0B = downtime;
        break; 
        case STOP:     // set low for 255 timer increments
            set_dir_pins(FWD);
            OCR0A = 255;
            OCR0B = 255;
        break;
        case BACKWD:    // reverse directions, PWM on both
            set_dir_pins(BACKWD);
            OCR0A = downtime;
            OCR0B = downtime;
        break;
        default:    // stop
            OCR0A = 255;
            OCR0B = 255;
        break;
    }
    
    // store new movement for set_turn_speed computation
    traversal_status = trav_value;  
}
*/
 
void update_wheel_control(){
    set_traversal_speed(1);
    //set_turn_speed(3);
}
 
void stop_wheel_control(){
    set_traversal_speed(0);
}
 