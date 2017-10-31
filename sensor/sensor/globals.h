#ifndef GLOBALS_H_
#define GLOBALS_H_

//Define enum for sources to ad converter
typedef enum {LINE, DIST_R, DIST_L} ad_source;

//Values for last sensor values
extern int line_center;
extern int line_state;
extern int ware_seen[];

//Values for calibration
extern int line_value[];
extern int floor_value[];
extern int line_threshold[];
extern int distance_blocked[];

//Variables used for ADC conversion
extern int adc_value;
extern int adc_done; //1 or 0

#endif /* GLOBALS_H_ */