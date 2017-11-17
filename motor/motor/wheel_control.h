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
    . is restricted to be max MOTOR_MAX in wheel_control.c
                                                                    */
int init_wheel_control(float base_speed);


/*  function:
    set a new speed for moving robot forward/backward or stop.
    Front of robot is based on where sensors are placed
    (2017-11-05).
    
    arg int trav_value :
    the new traversal value for moving the robot forward and
    backward. Set only to values:
    1  - forward
    0  - stop
    -1 - backward
                                                                    */
void set_traversal_speed(int trav_value);


/*  function:
    set new turning speed for robot rotation. Rotation is
    based on current traversal speed such that the robot will
    maintain same traversal movement when rotating. The rotation
    is scaled by the TURN_MAX constant and restricted by the
    MOTOR_MAX constant.
    
    arg int turn_value:
    the new turn speed setting. Can be set to any integer 
    value in the interval +/-7 where positive is right turn
    and 0 is no turning.
                                                                    */
void set_turn_speed(int turn_value);


/*  the "main-loop" of wheel control. Only used for testing so far. 
    intended use: call from the real main-loop of motor-unit.       
                                                                    */
void update_wheel_control();


#endif /* WHEEL_CONTROL_H_ */
