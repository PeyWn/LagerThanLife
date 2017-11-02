#include <avr/io.h>
#include "globals.h"

void start_ad_conversion(){
    ADCSRA = (1<<ADEN)|(1<<ADIE)|(1<<ADSC);
}

void set_ad_source(ad_source src){
    int bits[8];
    get_8bits(src, bits);

    ADMUX = (bits[0] << MUX0)|(bits[1] << MUX1)|(bits[2] << MUX2)|(1<<REFS0);
}

int convert_ad(ad_source src){   
    set_ad_source(src);
    start_ad_conversion();

	while(!adc_done) {
	}
	
    adc_done = 0;

    return adc_value;
}