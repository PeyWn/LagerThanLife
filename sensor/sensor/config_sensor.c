#include <avr/io.h>
#include <avr/interrupt.h>

/*
Setup AVR inputs and outputs, A/D converter and interrupts
*/
void setup_AVR(){
    // Set directions for input and outputs
    DDRA = (0<<DDA2)|(0<<DDA1)|(0<<DDA0);
    DDRB = (1<<DDB4)|(1<<DDB3)|(1<<DDB2)|(1<<DDB1)|(1<<DDB0);

    // Set A/D reference Vcc
    ADMUX = (1<<REFS0);
    // Enable A/D converter, enable interrupts for A/D converter
    ADCSRA = (1<<ADEN)|(1<<ADIE);

    //Enable interrupts for UART data recieved
    UCSRB = (1<<RXCIE);

    //Enable global interrupts
    sei();
}
