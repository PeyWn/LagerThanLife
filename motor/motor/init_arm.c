/*
 * init_arm.c
 *
 * Created: 11/3/2017 11:54:22 AM
 *  Author: jesjo430
 */ 

void init_IO(void)
{
	DDRD |= (1<<DDD4)|(1<<DDD3)&~(1<<DDD2);       //Set IO directions as follows: PORTD4 output, PORTD3 output, PORTD2 input. 

}