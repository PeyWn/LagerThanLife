/*
 * wheel_control.c
 *
 * Created: 10/31/2017 1:49:49 PM
 *  Author: jakno732
 */ 


#include <avr/io.h>


int init_dir_pins(void)
{
	PORTC |=  (1 << PORTC1) | (1 << PORTC0);
	return 0;
}

/* initialize phase correct PWM on pins OC0A and OC0B */
int init_PWM(void)
{
	// TNCT0 - timer 255 max
	// OCR0A - compare value A (PWM)
	// OCR0B - compare value B (PWM)
	
	TCCR0A = 0b11110001;	
	TCCR0B = 0b00000001;	//no prescaling. nothin 1 since PWM

	PORTC |= (1<<PORTC3) | (1<<PORTC4);

	OCR0A = 64;	//half low-period (downtime by test) 
	OCR0B = 30;

	DDRB |= (1<<DDB3) | (1<<DDB4); // set PB3, PB4 as outputs

	TIMSK0 |= (1<<OCIE0B)|(1<<OCIE0A);	// enable output compare interrupt
	return 0;
}


int main(void)
{
	init_dir_pins();
	init_PWM();
	
    while(1)
    {
		
    }
	return 0;
}