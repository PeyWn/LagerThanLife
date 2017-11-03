#include "wheel_control.h"

//variables for using timer in testing
unsigned    int period_counter  = 0;
unsigned    int second_counter  = 0;
            int has_counted     = 0;
            
//base speed of PWM, only changes when turning or stopping, set in init_wheel_control
 float   PWM_duty_ratio  = 0;

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

    set_traversal_speed(0);
    
    return 0;
}

void set_turn_speed(int turn_value){
    
}

void set_traversal_speed(int trav_value){
    
    //max(TCNT0)=255
    int uptime = 255 - PWM_duty_ratio*255;
    
    switch(trav_value){
        case 1:     // set
            PORTC |=  (1<<PORTC0);
            PORTC &= ~(1<<PORTC1);
            OCR0A = uptime;
            OCR0B = uptime;
            
        break; 
        case 0:     // set low for 255 timer increments
            OCR0A = 255;
            OCR0B = 255;
        break;
        case -1:    // reverse directions
            PORTC &= ~(1<<PORTC0);
            PORTC |=  (1<<PORTC1);
            OCR0A = uptime;
            OCR0B = uptime;
        break;
        default:    // stop
            OCR0A = 255;
            OCR0B = 255;
        break;
    }
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
 