/*
 * wheel_control.h
 *
 * Created: 11/2/2017 5:13:10 PM
 *  Author: jakno732
 */



#ifndef WHEEL_CONTROL_H_
#define WHEEL_CONTROL_H_
#include <avr/io.h>

/*  initial setup when motor unit is started 
    . sets registers that need to be set
    . enables PWM pins
    . enables DIR1 and DIR2 pins
    . sets initial output for these pins
*/
int init_wheel_control(unsigned int base_speed);

/* set a turn speed for both wheel sides 
   . turn value is an integer value between -7 and 7
   . a value higher than 7 would be interpreted as 7
   . a value lower than -7 would be interpreted as -7
 */
int set_turn_speed(int turn_value);

/* set a traversal speed for the robot
    arg "turn_value":
   . 1 is forward
   . 0 is stop
   . -1 i backward
   . other values are considered error and the robot should stop.
*/
int set_traversal_speed(int trav_value);


#endif /* WHEEL_CONTROL_H_ */
