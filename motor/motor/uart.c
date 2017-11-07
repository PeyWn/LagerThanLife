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
	 /* Activates USART0 and USART1. */
	  PRR0 &= ~(0<<PRUSART0)&~(0<<PRUSART1);
  
	/* Set baud rate. */
	UBRR1H = (unsigned char)(BAUDRATE>>8);
	 UBRR1L = (unsigned char)BAUDRATE;

	 /* Enable receiver and transmitter. */
	UCSR1B = (1<<RXEN1)|(1<<TXEN1);

	/* Set frame format: 8data, 1stop bit. Activate asynchronous UART. */ 
	UCSR1C |= (1<<USBS1)|(1<<UCSZ00)|(1<<UCSZ01)|(1<<UMSEL11)|(1<<UMSEL10);
	UCSR1C &= ~(1<<USBS0)&~(1<<UCSZ02);
}


/* Writes input data to transmit buffer. */
void usart_transmit( unsigned char data )
{ 
	while (!(UCSR1A&(1<<UDRE1)));    //Wait for empty transmit buffer 
	UDR1 = data;                     //Put data into buffer, sends the data
}


unsigned char usart_recieve (void)
{
	while((!(UCSR0A)) & (1<<RXC0));          // wait while data is being received
	return UDR1;                          // return 8-bit data
}
