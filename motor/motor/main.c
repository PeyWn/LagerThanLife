/*
 * motor.c
 *
 * Created: 11/1/2017 8:55:44 AM
 *  Author: jakno732
 */ 


#include <avr/io.h>
#include "uart.h"
#include "init_arm.h"

int main(void)
{
	init_IO();
	usart_init();
	PORTD |= (1<<PORTD4);
	
	while(1)
    {
		usart_transmit(0b00000000);
    }
}