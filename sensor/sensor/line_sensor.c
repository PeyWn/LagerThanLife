﻿#include <stdlib.h>
#include <math.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>
#include "globals.h"
#include "line_sensor.h"
#include "ad_conversion.h"

#define F_CPU 16000000UL
#include <util/delay.h>

const int LED_DELAY = 10; //delay for led to turn on in us


void calibrate_line() {
    get_linesensor_values(line_value);
    update_line_threshold();
}


void calibrate_floor() {
    get_linesensor_values(floor_value);
    update_line_threshold();
}

void update_line_threshold() {
    for(int i = 0; i < 11; i++) {
        line_threshold[i] = round((line_value[i] - floor_value[i])/2.0);
    }
}


void get_linesensor_values(int sensor_res[]) {
		for(int i = 0; i < 11; i++){
    		mux_select(i);
    		set_led(true);
    		_delay_us(LED_DELAY);
    		
    		sensor_res[i] = convert_ad(LINE);

    		set_led(false);
		}
}


void mux_select(int i){
    //Generate bits from int
    int bits[8];
    get_8bits(i, bits);

    //Set mux control
    set_bit(&PORTB, PB3, bits[3]);
    set_bit(&PORTB, PB2, bits[2]);
    set_bit(&PORTB, PB1, bits[1]);
    set_bit(&PORTB, PB0, bits[0]);
}


void set_led(bool state){
    set_bit(&PORTB, PB4, state);
}

line_sensor_state calc_line_state(volatile bool detected[], int sum){
    bool double_line = false;

    bool detect_found = false; //detecting sensor found
    int empty_row = 0; //non-detecting sensors in row

    for(int i = 0; i < 11 && !double_line; i++){
        if(detected[i]){

            //double line detected
            //i is detecting line
            if(empty_row >= 2 && detect_found){
                double_line = true;
            }

            detect_found = true;
            empty_row = 0;
        }
        else{
            //i is not detecting line
            empty_row++;
        }
    }

    //Set state depending on sum and double_line
    line_sensor_state new_state;
    if(sum == 0 || double_line){
        new_state = NONE_DOUBLE;
    }
    else if(sum >= 1 && sum <= 3){
        new_state = SINGLE;
    }
    else{
        new_state = CORNER;
    }

    return new_state;
}


int calc_line_center(volatile bool detected[], int sum){
    float sum_weighted = 0;

    //Iterate to calculate weighted sum of detected
    for(int i = 0; i < 11; i++){
        if(i < 5){
            sum_weighted += -abs(i - 5)*detected[i];
        }
        else{
            sum_weighted += abs(i - 5)*detected[i];
        }
    }

    //Make number between +-127
    int new_line_center = round((127.0/5.0) * (sum_weighted/(float)sum));

    //Overwrite old line_center
    return new_line_center;
}

void update_line_parameters(volatile bool detected[]){
    int sum = 0;

    //Iterate to calculate sum of detecting sensors
    for(int i = 0; i < 11; i++){
        sum += detected[i];
    }

    //update parameters
    //turn off interrupts while changing
    cli();
    line_center = calc_line_center(detected, sum);
    line_state = calc_line_state(detected, sum);
    sei();
}