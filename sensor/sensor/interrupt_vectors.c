#include <avr/interrupt.h>
#include "globals.h"

/*
Define interrupt vector for ADC conversion complete.
*/
ISR(ADC_vect){
	adc_value = ADC;
    adc_done = true;
}

/*
Define interrupt vector for UART data received.
*/
ISR(USART_RXC_vect){
	volatile uint8_t data_read = UDR;
	
	UDR = data_read;
}