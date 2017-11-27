/*
 * uart.c
 *
 * Created: 11/2/2017 10:55:44 AM
 *  Author: jesjo430, bjohv276
 */ 

#include <stdio.h>
#include <avr/io.h>
#include <stdlib.h>
#include "uart.h"
#include "globals.h" 

void usart_init(int baudrate)
{
	/* Calculate baud according to formula given in data sheet. */ 
	int baud = (((F_CPU)/(baudrate*16UL))-1);
	
	baud = 0; //HACK: CHANGED TO CALCULATED VALUE. 
	
	/* Set baud rate to 1M @ max 1Mb/s. */
	UBRR1H = (unsigned char)(baud>>8);
	UBRR1L = (unsigned char)baud;
	
	/* Disable double asynchronous speed */
	UCSR1A &= ~(1<<U2X1);
	
	/* Enable receiver and transmitter on USART1*/
	UCSR1B |= (1<<RXEN1)|(1<<TXEN1);  

	/* 0b00000011: asynchronous[00], no parity [00], 1 stop-bit [0], 8 data bits [11], Rising XCKn edge [0] */
	UCSR1C |= (3<<UCSZ10);

	/* Enable global interrupt */ 
	SREG |= (1<<7);
}

void usart_transmit( unsigned char data )
{ 
	while (!(UCSR1A&(1<<UDRE1)));  //Wait for empty transmit buffer.
	UDR1 = data;				   //Put data into buffer, sends the data
	while (!(UCSR1A&(1<<TXC1)));   //Wait for empty transmit register (adds delay after sent byte)
	UCSR1A |= (1<<TXC1);		   //clear transmit register empty flag by setting TXC1. 
}


unsigned char usart_receive (void)
{
	
	while(!(UCSR1A & (1<<RXC1)));  // wait for data to be received in receiver buffer
	volatile char data = UDR1;
	return data;
}