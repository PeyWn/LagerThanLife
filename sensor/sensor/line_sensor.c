#include <avr/io.h>

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
    PORTB = (bits[0]<<PB0)|(bits[1]<<PB1)|(bits[1]<<PB1)|(bits[1]<<PB1);
}

/*
Sets the output to the led on the line sensor

state - 1 or 0, on or off
*/
void set_led(int state){
    PORTB = (state<<PB4);
}