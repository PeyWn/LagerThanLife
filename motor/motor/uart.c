#include <stdio.h>
#include <avr/io.h>
#include <stdlib.h>
#include "uart.h"
#include "globals.h"
#include <avr/io.h>
#include <avr/interrupt.h>

void usart1_init()
{
	/* Calculate baud according to formula given in data sheet. */
	// int baud = (((F_CPU)/(baudrate*16UL))-1);

	int baud = 0; // directly calculated value of baud for 1 megabaud.

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

void usart0_init(){
    /* DDRD = (0<<DDD0)|(1<<DDD1); */
    DDRD |=  (1<<DDD1);
    DDRD &= ~(1<<DDD0);

    UBRR0L = 0x33; //BAUDRATE 33 = 19200

    /* Set UART baudrate, activates Tx/Rx, activates interrupts for UART data recieved */
    UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);

    /* Enable global interrupts */
    sei();
}

void usart_transmit( unsigned char data )
{
	while (!( UCSR1A & (1<<UDRE1) ));   // Wait for empty transmit buffer.
	UDR1 = data;				        // send data

	while (!( UCSR1A & (1<<TXC1) ));    // always wait for data shifted out => no double-buffer
	UCSR1A |= (1<<TXC1);		        // clear TXC1 (empty shift-register) by setting TXC1.
}

unsigned char usart_receive (void)
{
	volatile char test = 1;
	while(!( UCSR1A & (1<<RXC1)));  // wait for data to be received in receiver buffer
	volatile char data = UDR1;
	return data;
}
