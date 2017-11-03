#include <avr/io.h>
#include "globals.h"
#include "config_sensor.h"

void start_ad_conversion(){
    set_bit(&ADCSRA, ADSC, 1);
}

void set_ad_source(ad_source src){
    int bits[8];
    get_8bits(src, bits);
    
    set_bit(&ADMUX, MUX0, bits[0]);
    set_bit(&ADMUX, MUX1, bits[1]);
    set_bit(&ADMUX, MUX2, bits[2]);
}

int convert_ad(ad_source src){   
    set_ad_source(src);
    start_ad_conversion();

	while(!adc_done) {
	}
	
    adc_done = 0;

    return adc_value;
}