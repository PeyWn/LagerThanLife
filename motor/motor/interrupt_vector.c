#include <avr/interrupt.h>


/*
Define interrupt vector for UART data received.
*/
ISR(USART0_RX_vect){
	volatile uint8_t data_read = UDR0;
	
	UDR0 = data_read;
}