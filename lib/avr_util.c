/*
*
*       UTILITY FUNCTIONS 
*
*/

#include "avr_util.h"

void get_8bits(int n, int ar[]){
    for(int i = 0; i < 8; i++){
        ar[i] = (n >> i) & 1;
    }
}

void set_bit(volatile uint8_t* reg, int bit_n, bool value){
    if(value){
        //set 1
        *reg |= (1 << bit_n);
    }
    else{
        //set 0
        *reg &= ~(1 << bit_n);
    }
}
