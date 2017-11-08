/*
 * uart_arm.c
 *
 * Created: 2017-11-04 17:36:19
 *  Author: Jesper
 */  

#include <stdio.h>
#include <avr/io.h>
#include <stdlib.h>
#include "uart_arm.h"
#include "uart.h"

#define DIRECTION_PORT PORTD	     // Direction port D4 on AVR.

void set_direction_port(int dir)
{
    if (dir == TRANSMIT)
    {
        DIRECTION_PORT |= (1<<PORTD4);		// Shift 1 4 steps into PORTD.
    }
    else if (dir == RECEIVE)
    {
        DIRECTION_PORT &= ~(1<<PORTD4);		// Set bit 4 in PORTD to 0.
    }
}

void transmit(unsigned char data)
{	
	set_direction_port(TRANSMIT);
	UCSR1A |= (1<<TXC1); //Reset transmit done flag. 
	usart_transmit(data); 
}

unsigned char receive(void)
{	
	set_direction_port(RECEIVE); 
	return usart_receive();
}