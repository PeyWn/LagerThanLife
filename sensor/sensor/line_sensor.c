#include <avr/io.h>
#include "globals.h"

/*
Switch the MUXes controlling the line sensor to input and output i.

i - the led+phototransistor the MUXes should set+read from,
    must be between 0 and 10
*/
void mux_select(int i){
    //Generate bits from int
    int bits[8];
    get_8bits(i, bits);

    //Set mux control
    PORTB = (PORTB & 0b11110000) | (bits[3]<<PB3)|(bits[2]<<PB2)|(bits[1]<<PB1)|(bits[0]<<PB0);
}

/*
Sets the output to the led on the line sensor

state - 1 or 0, on or off
*/
void set_led(bool state){
    PORTB = (PORTB & 0b11101111) | (state<<PB4);
}