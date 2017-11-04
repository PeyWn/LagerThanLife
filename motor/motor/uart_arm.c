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

#define F_CPU 16000000				 // System clock frequency
#define BAUD 9600					 // Baud rate
#define RECIEVE 0					 // Definition used when setting half duplex UART direction. 
#define TRANSMIT 1					 // Definition used when setting half duplex UART direction.
#define DIRECTION_PORT = PORTD4		 // Direction port D4 on AVR.

void transmit(unsigned char data)
{
	DIRECTION_PORT = TRANSMIT;		// Half duplex UART demands setting direction. 
	usart_transmit(data);
}

unsigned char receive(void)
{
	DIRECTION_PORT = RECIEVE;		// Half duplex UART demands setting direction. 
	return usart_transmit();
}