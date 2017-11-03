/*
 * wheel_control.h
 *
 * Created: 11/2/2017 5:13:10 PM
 *  Author: jakno732
 */

#ifndef WHEEL_CONTROL_H_
#define WHEEL_CONTROL_H_
#include <avr/io.h>

/*  initial setup for wheel control when AVR-unit is started
    . sets registers that need to be set
    . enables PWM pins
    . enables DIR1 and DIR2 pins
    . sets initial output for these pins
    arg base_speed:
    . the set speed for traversal speed
    . it is the duty of PWM
    . turn speed will be based on the current speed
*/
int init_wheel_control(float base_speed);

/* set a turn speed for both wheel sides 
   . turn value is an integer value between -7 and 7
   . a value higher than 7 would be interpreted as 7
   . a value lower than -7 would be interpreted as -7
   . turn speed is dependent on the current traversal speed
 */
void set_turn_speed(int turn_value);

/* set a traversal speed for the robot
    arg "turn_value":
   . 1 is forward
   . 0 is stop
   . -1 i backward
   . other values are considered error and the robot should stop.
*/
void set_traversal_speed(int trav_value);

/* the "main-loop" of wheel control, run this when wheel control is running */
void update_wheel_control();

/* stop all motion from wheel_control
   it is ok to just set speeds to 0. */
void stop_wheel_control();


#endif /* WHEEL_CONTROL_H_ */
