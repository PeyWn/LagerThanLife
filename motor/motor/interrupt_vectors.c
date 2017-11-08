/*
 * interrupt_vectors.c
 *
 * Created: 11/8/2017 11:34:07 AM
 *  Author: jesjo430
 */ 

#include <avr/interrupt.h>
#include "globals.h"

ISR(USART1_RX_vect) 
{
	UCSR1A |= (1<<RXC1); //Reset receive done flag. 
}

ISR(USART1_TX_vect)
{
	UCSR1A |= (1<<TXC1); //Reset transmit done flag. 
}

ISR(USART1_UDRE_vect)
{
	UCSR1B |= (1<<UDR1); 
}