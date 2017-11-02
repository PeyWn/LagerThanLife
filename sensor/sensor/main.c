#include <avr/io.h>
#include "globals.h"

//TMP include
#include <stdio.h>

#define F_CPU 8000000UL
#include <util/delay.h>

//Definitions of globals
int line_center = 0;
line_sensor_state line_state = 0;
int ware_seen[2] = {0,0};

int line_value[11];
int floor_value[11];
int line_threshold[11] = {400,400,400,400,400,400,400,400,400,400,400};
int distance_blocked[2];

int adc_value = 0;
volatile bool adc_done = 0; //1 or 0

int main(void)
{	
    run_tests();

    setup_AVR();
	
	volatile bool detected[11];
    //MAIN LOOP
    while(true)
    {
		for(int i = 0; i < 11; i++){
			mux_select(i);
			set_led(true);
			_delay_ms(10);
			adc_value = convert_ad(LINE);
			
			if(adc_value > line_threshold[i]) {
				detected[i] = true;
			} else {
				detected[i] = false;
			}
			set_led(false);
		}
		
		printf("\n");
		
		// update_line_parameters(detected)
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