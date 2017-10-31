#include <avr/io.h>
#include "globals.h"

//Definitions of globals
int line_center = 0;
int line_state = 0;
int ware_seen[2] = {0,0};

int line_value[11];
int floor_value[11];
int line_threshold[11];
int distance_blocked[2];

int adc_value = 0;
int adc_done = 0; //1 or 0

int main(void)
{
    setup_AVR();

    convert_ad(DIST_L);

    //MAIN LOOP
    while(1)
    {
        
    }
}

/*
Generate array of size 8 with 1/0 for every bit in the binary representation of
the number n.

n - number to convert to binary
ar - array to save "bits" (integer of value 1/0) in
*/
void get_8bits(int n, int ar[]){
    for(int i = 0; i < 8; i++){
        ar[i] = (n >> i) & 1;
    }
}