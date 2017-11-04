//#define TEST

#include <avr/io.h>
#include "globals.h"
#include "line_sensor.h"
#include "ad_conversion.h"
#include "config_sensor.h"
#include "ware_sensor.h"

//Definitions of globals
int line_center = 0;
line_sensor_state line_state = NONE_DOUBLE;
bool ware_seen[2] = {false, false};

int line_value[11];
int floor_value[11];

int line_threshold[11] = {300,300,300,300,300,300,300,300,300,300,300};
int distance_blocked[2] = {100, 100};

int adc_value = 0;
volatile bool adc_done = 0; //1 or 0

int main(void)
{	
    #ifdef TEST
    run_tests();
    #endif

    setup_AVR();
	
    //Array for line sensor values
	volatile bool detected[11];
    
    //MAIN LOOP
    while(true)
    {

        int sensor_values[11];

        get_linesensor_values(sensor_values);

    	for(int i = 0; i < 11; i++){
        	detected[i] = (sensor_values[i] > line_threshold[i]);
    	}

		
        //Update line_center and line_sensor
		update_line_parameters(detected);

        //Read and update ware sensors
        update_ware_seen();
    }
}