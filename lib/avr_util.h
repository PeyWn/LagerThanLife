#ifndef AVR_UTIL_H_
#define AVR_UTIL_H_

#include <avr/io.h>

//Define booleans for C
typedef int bool;
#define true 1
#define false 0

/*
Generate array of size 8 with 1/0 for every bit in the binary representation of
the number n.

n - number to convert to binary
ar - array to save "bits" (integer of value 1/0) in
*/
void get_8bits(int n, int ar[]);

/*
Sets bit nr n in the given 8 bit register to the given value

reg - pointer to register to change
bit_n - the bit to change (0-7)
value - the value to set the bit to, 1 or 0 (true/false)
*/
void set_bit(volatile uint8_t* reg, int bit_n, bool value);

#endif /* AVR_UTIL_H_ */
