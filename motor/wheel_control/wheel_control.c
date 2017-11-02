/*
 * wheel_control.c
 *
 * Created: 10/31/2017 1:49:49 PM
 *  Author: jakno732, joael543
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
	// TCNT0 - timer 255 max
	// OCR0A - compare value A (PWM)
	// OCR0B - compare value B (PWM)
	
	TCCR0A = 0b11110001;	
	TCCR0B = 0b00000001;	//no pre-scaling. nothing is 1 since PWM

	PORTC |= (1<<PORTC3) | (1<<PORTC4);

	OCR0A = 255;	//half low-period (downtime by test) 
	OCR0B = 255;

	DDRB |= (1<<DDB3) | (1<<DDB4); // set PB3, PB4 as outputs

	TIMSK0 |= (1<<OCIE0B)|(1<<OCIE0A);	// enable output compare interrupt
	return 0;
}

/*	check if a specified amount of seconds has passed since started counting
	
*/
int seconds(unsigned int seconds, unsigned int* period_counter, unsigned int* second_counter, int* has_counted){
	if ( TCNT0 > 200 && !(*has_counted)){
		*has_counted = 1; 
		*period_counter += 1; 
	}
	else if ( TCNT0 < 200 ){
		*has_counted = 0; 
	}
	if ( *period_counter >= 15770 ){ // 15770Hz is measured in oscilloscope (8Mhz)
		*second_counter += 1;
		*period_counter = 0;
	}
	if (*second_counter > seconds){
		*second_counter = 0;
		return 1;
	}
	else
	{
		return 0;
	}
}


// f = 1/T; T=1/f; 16000 cycles > 1s
int main(void)
{
	init_dir_pins();
	init_PWM();
	
	unsigned int period_counter = 0; 
	unsigned int second_counter = 0;
	int has_counted = 0; 
	
	while(!seconds(5, &period_counter, &second_counter, &has_counted));		//wait 5 sec
	OCR0A = 100;
	OCR0B = 100;
	while(!seconds(2, &period_counter, &second_counter, &has_counted));	//wait 5 sec
	OCR0A = 255;
	OCR0B = 255;

    while(1)  
    {
		
    }
	return 0;
}