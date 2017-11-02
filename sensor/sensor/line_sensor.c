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

/*
Calculate new value for amount of lines seen.

detected - 11 long array signaling wheter line sensor i detects line
sum - amount of sensors detecting a line

return - new value for the state of lines detected
*/
line_sensor_state calc_line_state(bool detected[], int sum){
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
    if(sum == 0 && double_line){
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

/*
Calculate new value for the cetner of the line.

detected - 11 long array signaling wheter line sensor i detects line
sum - amount of sensors detecting a line

return - new value for the center of line, between +-127
*/
int calc_line_center(bool detected[], int sum){
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

/*
Update line sensor parameters line_state and line_sensor based on a
new sensor reading.

detected - 11 long array signaling wheter line sensor i detects line
*/
void update_line_parameters(bool detected[]){
    int sum = 0;

    //Iterate to calculate sum of detecting sensors
    for(int i = 0; i < 11; i++){
        sum += detected[i];
    }

    //update parameters
    line_center = calc_line_center(detected, sum);
    line_state = calc_line_state(detected, sum);
}