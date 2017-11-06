/*/*
 * init_arm.c
 *
 * Created: 11/3/2017 11:54:22 AM
 *  Author: jesjo430
 */ 

#include <avr/io.h>
#include "init_arm.h"

void init_IO(void)
{
	DDRD |= (1<<DDD4)|(1<<DDD3);       //Set IO directions as follows: PORTD4 output, PORTD3 output.
	DDRD &= ~(1<<DDD2);				   //PORTD2 input. 
}