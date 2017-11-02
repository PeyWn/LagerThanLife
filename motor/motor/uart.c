/*
 * uart.c
 *
 * Created: 11/2/2017 10:55:44 AM
 *  Author: jesjo430
 */ 

#include <stdio.h>

#define BAUD_RATE = 1000000; 

void USART_Init(unsigned int BAUD_RATE)
{
	UBRRn = 0; //Setting the XCKn port pin as output, enables master mode.
	XCKn_DDR |= (1<<XCKn); //Set MSPI mode of operation and SPI data mode 0.
	UCSRnC = (1<<UMSELn1)|(1<<UMSELn0)|(0<<UCPHAn)|(0<<UCPOLn //Enable receiver and transmitter.
	UCSRnB = (1<<RXENn)|(1<<TXENn //Set baud rate.
	
	//IMPORTANT: The Baud Rate must be set after the transmitter is enabled
	UBRRn = baud;
}