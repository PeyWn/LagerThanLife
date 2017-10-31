#include <avr/interrupt.h>
#include "globals.h"

/*
Define interrupt vector for ADC conversion complete.
*/
ISR(ADC_vect){
    //TODO implement ISR
    adc_done = 1;
}

/*
Define interrupt vector for UART data received.
*/
ISR(USART_RXC_vect){
    //TODO implement ISR
}