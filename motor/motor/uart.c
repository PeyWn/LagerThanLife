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

#define F_CPU 16000000    // Avr system clock @ 16Mhz. 

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
	
	/* Enable receiver and transmitter on USART1, also interrupt flags. */
<<<<<<< HEAD
	UCSR1B |= (1<<RXEN1)|(1<<TXEN1);
=======
	UCSR1B |= (1<<RXCIE1)|(1<<TXCIE1)|(1<<UDRIE1)|(1<<RXEN1)|(1<<TXEN1);
>>>>>>> parent of 6fd476a... Show anders Commit
	
	/* 0b00000011: asynchronous[00], no parity [00], 1 stop-bit [0], 8 data bits [11], Rising XCKn edge [0] */
	UCSR1C |= (3<<UCSZ10);

	/* Enable global interrupt */ 
	SREG |= (1<<7);
}


/* Writes input data to transmit buffer. */
void usart_transmit( unsigned char data )
{ 
	while (!(UCSR1A&(1<<UDRE1)));		 //Wait for empty transmit buffer.
	UDR1 = data;						 //Put data into buffer, sends the data
<<<<<<< HEAD
	while (!(UCSR1A&(1<<TXC1)));		 //Wait for empty transmit register
	UCSR1A |= (1<<TXC1);				 //clear transmit register empty flag by setting TXC1. 
=======
	
>>>>>>> parent of 6fd476a... Show anders Commit
}


unsigned char usart_receive (void)
{
<<<<<<< HEAD
	while((!(UCSR1A)) & (1<<RXC1));          // wait for data to be received in receiver buffer
	char data = UDR1;                             // return 8-bit data
	return data;
=======
    //while(!UDR1);   //wait if there is no data
	while((!(UCSR1A)) & (1<<RXC1));          // wait while data is being received
	return UDR1;                             // return 8-bit data
>>>>>>> parent of 6fd476a... Show anders Commit
}