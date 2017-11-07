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

#define F_CPU 16000000    // AVR SYS CLOCK FREQUENCY TO 16MHz
#define BAUD 1000000         // DEFINE BAUD RATE 1M Baud
#define BAUDRATE ((F_CPU)/(BAUD*16UL)-1)    // SET BAUDRATE VALUE FOR UBRR

void usart_init(void)
{
	/* Set baud rate to 1M @ max 2Mb/s. */
	UBRR1L = 0;
	UBRR1H = 0;
	
	/* Set Double asynchronous speed */
	UCSR1A |= (1<<U2X1);
	
	/* 0b00000011: asynchronous[00], no parity [00], 1 stop-bit [0], 8 data bits [11], Rising XCKn edge [0] */
	UCSR1C = 0b00000110;

	/* Enable receiver and transmitter on USART1, also interrupt flags. */
	UCSR1B |= (1<<RXCIE1)|(1<<TXCIE1)|(1<<UDRIE1)|(1<<RXEN1)|(1<<TXEN1);
}


/* Writes input data to transmit buffer. */
void usart_transmit( unsigned char data )
{ 
	while (!(UCSR1A&(1<<UDRE1)));    //Wait for empty transmit buffer 
	UDR1 = data;                      //Put data into buffer, sends the data
}


unsigned char usart_receive (void)
{
    //while(!UDR1);   //wait if there is no data
	while((!(UCSR1A)) & (1<<RXC1));          // wait while data is being received
	return UDR1;                             // return 8-bit data
}
