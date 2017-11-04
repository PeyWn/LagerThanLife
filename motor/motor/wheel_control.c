#include    "wheel_control.h"

/* LOKAL CONSTANTS */
#define     LEFT        0
#define     RIGHT       1
#define     FWD         2
#define     BACKWD      3
#define     TURN_MAX    0.3f    // turn speed +/-7 => TURN_MAX higher/lower PWM


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
/*
void set_turn_speed(int turn_value){
    float turn_speed    =  turn_value * TURN_MAX/7
    float left_speed    =  traversal_status * PWM_duty_ratio;
    float right_speed   = -traversal_status * PWM_duty_ratio;
    
    if (left_speed + turn > 1){
        
    }else if(){
        
    }else if(){
        
    }else if(){
        
    }
}
*/

void set_traversal_speed(int trav_value){
    
    //max(TCNT0)=255
    int downtime = 255 - PWM_duty_ratio*255;
    
    switch(trav_value){
        case 1:     // set forward speed
            set_dir_pins(FWD);
            OCR0A = downtime;
            OCR0B = downtime;
        break; 
        case 0:     // set low for 255 timer increments
            set_dir_pins(FWD);
            OCR0A = 255;
            OCR0B = 255;
        break;
        case -1:    // reverse directions, PWM on both
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
 
void update_wheel_control(){
    while(!seconds(3));		//wait 5 sec
    set_traversal_speed(1);
    while(!seconds(2));	//wait 5 sec
    set_traversal_speed(0);
    while(!seconds(1));	//wait 5 sec
    set_traversal_speed(-1);
    while(!seconds(2));	//wait 5 sec
    set_traversal_speed(0);
}
 
void stop_wheel_control(){
    set_traversal_speed(0);
}
 