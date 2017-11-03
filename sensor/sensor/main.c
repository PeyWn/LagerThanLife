//#define TEST
#define F_CPU 8000000UL //TODO set correct clock

#include <avr/io.h>
#include <util/delay.h>

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

//TODO implement calibration
int line_threshold[11] = {400,400,400,400,400,400,400,400,400,400,400};
int distance_blocked[2] = {100, 100};

int adc_value = 0;
volatile bool adc_done = 0; //1 or 0

const int LED_DELAY = 10; //delay for led to turn on in us

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
		for(int i = 0; i < 11; i++){
			mux_select(i);
			set_led(true);
			_delay_us(LED_DELAY);
			adc_value = convert_ad(LINE);
			
		    detected[i] = (adc_value > line_threshold[i]);

			set_led(false);
		}
		
        //Update line_center and line_sensor
		update_line_parameters(detected);

        //Read and update ware sensors
        update_ware_seen();
    }
}