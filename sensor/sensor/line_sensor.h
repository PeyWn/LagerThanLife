#ifndef LINE_SENSOR_H_
#define LINE_SENSOR_H_

/*
Calibrate linesensors when all sensors are on a line
*/
void calibrate_line();

/*
Calibrate linesensors when all sensors are not on a line
*/
void calibrate_floor();

/*
Update line_threshold based on line_value and floor_value
*/
void update_line_threshold();

/*
Get linesensor values by converting a/d and writing reading to sensor_res

sensor_res - 11 long array to save the sensor reading value in
*/
void get_linesensor_values(int sensor_res[]);

/*
Switch the MUXes controlling the line sensor to input and output i.

i - the led+phototransistor the MUXes should set+read from,
    must be between 0 and 10
*/
void mux_select(int i);

/*
Sets the output to the led on the line sensor

state - 1 or 0, on or off
*/
void set_led(bool state);

/*
Calculate new value for amount of lines seen.

detected - 11 long array signaling wheter line sensor i detects line
sum - amount of sensors detecting a line

return - new value for the state of lines detected
*/
line_sensor_state calc_line_state(volatile bool detected[], int sum);

/*
Calculate new value for the cetner of the line.

detected - 11 long array signaling wheter line sensor i detects line
sum - amount of sensors detecting a line

return - new value for the center of line, between +-127
*/
int calc_line_center(volatile bool detected[], int sum);

/*
Update line sensor parameters line_state and line_sensor based on a
new sensor reading.

detected - 11 long array signaling whether line sensor i detects line
*/
void update_line_parameters(volatile bool detected[]);

#endif /* LINE_SENSOR_H_ */