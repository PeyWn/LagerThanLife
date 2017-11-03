/*
 * uart.c
 *
 * Created: 11/2/2017 10:55:44 AM
 *  Author: jesjo430, bjohv276
 */ 

#include <stdio.h>
#include <stdlib.h>
#include "uart.h"

#define F_CPU 16000000    // AVR SYS CLOCK FREQUENCY TO 16MHz
#define BAUD 9600         // DEFINE BAUD RATE
#define BAUDRATE ((F_CPU)/(BAUD*16UL)-1)    // SET BAUDRATE VALUE FOR UBRR

void usart_init(void)
{
  /* Set baud rate */
  UBRRHn = (unsigned char)(BAUDRATE>>8);
  UBRRLn = (unsigned char)BAUDRATE;

  /* Enable receiver and transmitter */
  UCSRnB = (1<<RXENn)|(1<<TXENn);

  /* Set frame format: 8data, 2stop bit */
  UCSRnC = (1<<USBSn)|(3<<UCSZn0);
}


void usart_transmit( unsigned char data )
{ 
  while ( !( UCSRnA & (1<<UDREn)) );    //Wait for empty transmit buffer 
  UDRn = data;                          //Put data into buffer, sends the data
}


unsigned char uart_recieve (void)
{
  while(!(UCSRA) & (1<<RXC));          // wait while data is being received
  return UDR;                          // return 8-bit data
}

