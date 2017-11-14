/*/*
 * init_arm.c
 *
 * Created: 11/3/2017 11:54:22 AM
 *  Author: jesjo430
 */ 

#include <avr/io.h>
#include "init_arm.h"
#include "globals.h"
#include "transmission.h"

void init_IO(void)
{
	DDRD |= (1<<DDD4)|(1<<DDD3);       //Set IO directions as follows: PORTD4 output, PORTD3 output.
	DDRD &= ~(1<<DDD2);				   //PORTD2 input. 
}

void set_limits(void)
{
	write_word(1, CW_ANGLE_LIMIT_ADDRESS, CW_LIMIT_1, WRITE_DATA);
	write_word(1, CW_ANGLE_LIMIT_ADDRESS, CCW_LIMIT_1, WRITE_DATA);
	
	write_word(2, CW_ANGLE_LIMIT_ADDRESS, CW_LIMIT_1, WRITE_DATA);
	write_word(2, CCW_ANGLE_LIMIT_ADDRESS, CCW_LIMIT_1, WRITE_DATA);
	
	write_word(3, CW_ANGLE_LIMIT_ADDRESS, CW_LIMIT_3, WRITE_DATA);
	write_word(3, CCW_ANGLE_LIMIT_ADDRESS, CCW_LIMIT_3, WRITE_DATA);
	
	write_word(4, CW_ANGLE_LIMIT_ADDRESS, CW_LIMIT_4, WRITE_DATA);
	write_word(4, CW_ANGLE_LIMIT_ADDRESS, CCW_LIMIT_4, WRITE_DATA);
		
	write_word(5, CW_ANGLE_LIMIT_ADDRESS, CW_LIMIT_5, WRITE_DATA);
	write_word(5, CCW_ANGLE_LIMIT_ADDRESS, CCW_LIMIT_5, WRITE_DATA);
		
	write_word(6, CW_ANGLE_LIMIT_ADDRESS, CW_LIMIT_6, WRITE_DATA);
	write_word(6, CCW_ANGLE_LIMIT_ADDRESS, CCW_LIMIT_6, WRITE_DATA);
	
	write_word(7, CW_ANGLE_LIMIT_ADDRESS, CW_LIMIT_7, WRITE_DATA);
	write_word(7, CCW_ANGLE_LIMIT_ADDRESS, CCW_LIMIT_7, WRITE_DATA);
		
	write_word(8, CW_ANGLE_LIMIT_ADDRESS, CW_LIMIT_8, WRITE_DATA);
	write_word(8, CCW_ANGLE_LIMIT_ADDRESS, CCW_LIMIT_8, WRITE_DATA);
}

