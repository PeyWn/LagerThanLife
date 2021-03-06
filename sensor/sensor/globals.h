﻿#ifndef GLOBALS_H_
#define GLOBALS_H_

#include "../../lib/avr_util.h"

//Define enum for sources to ad converter
typedef enum {LINE, DIST_R, DIST_L} ad_source;

//Enum for the state of line detection
typedef enum {NONE_DOUBLE, SINGLE, CORNER} line_sensor_state;

//Values for last sensor values
extern int line_center;
extern line_sensor_state line_state;
extern bool ware_seen[];

//Values for calibration
extern int line_value[];
extern int floor_value[];
extern int line_threshold[];
extern int distance_blocked[];

//Variables used for ADC conversion
extern int adc_value;
extern volatile bool adc_done;

//Flags to signal calibration next iteration
extern bool do_calibrate_ware;
extern bool do_calibrate_floor;
extern bool do_calibrate_line;

#endif /* GLOBALS_H_ */
