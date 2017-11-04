#include <avr/interrupt.h>

#include "globals.h"
#include "ad_conversion.h"

void update_ware_seen(){
    volatile bool new_reading[2] = {false, false};
    int reading; //temporary saved value of last reading

    reading = convert_ad(DIST_R);
    new_reading[0] = (reading > distance_blocked[0]);

    reading = convert_ad(DIST_L);
    new_reading[1] = (reading > distance_blocked[1]);

    //update ware_seen
    //turn off interrupts to not get inconsistent values
    cli();
    ware_seen[0] = new_reading[0];
    ware_seen[1] = new_reading[1];
    sei();
}


void calibrate_waresensor() {
    distance_blocked[0] = convert_ad(DIST_R);
    distance_blocked[1] = convert_ad(DIST_L);
}