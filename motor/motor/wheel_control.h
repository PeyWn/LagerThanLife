/*
 * wheel_control.h
 *
 * Created: 11/2/2017 5:13:10 PM
 *  Author: jakno732
 */

#ifndef WHEEL_CONTROL_H_
#define WHEEL_CONTROL_H_
#include <avr/io.h>

/* max speeds: +/- interval for possible integer settings */
#define MAX_TRAV_SETTING 7  // traversal speed settings
#define MAX_TURN_SETTING 7  // turn speed settings

/*  initial setup for wheel control when AVR-unit is started
    . sets registers that need to be set
    . enables PWM pins
    . enables DIR1 and DIR2 pins
    . set speeds to 0
                                                                    */
int init_wheel_control();

/* return the current traversal speed */
int get_traversal_status();

/* return the current turn speed */
int get_turn_status();

/*  set a new speed for moving robot forward/backward or stop.
    Front of robot is based on where sensors are placed
    (2017-11-05). Traversal speed is saturated at MAX_TRAV_SETTING
    constant.
    
    arg int trav_value :
    the new traversal value for moving the robot forward and
    backward. Values explained:
    +1 ...  MAX_TRAV_SETTING  -> forward
     0                        -> stop
    -1 ... -MAX_TRAV_SETTING  -> backward
                                                                    */
void set_traversal_speed(int trav_value);


/*  set new turning speed for robot rotation. Rotation is
    based on current traversal speed such that the robot will
    maintain same traversal movement when rotating. The rotation
    is scaled by the TURN_MAX constant and restricted by the
    MOTOR_MAX constant. Turn-speed is alse saturated at 
    MAX_TURN_SETTING constant.
    
    arg int turn_value:
    the new turn speed setting. Can be set to any integer 
    value in the interval +/-7 where positive is right turn
    and 0 is no turning.
                                                                    */
void set_turn_speed(int turn_value);

/*  Update parameter for traversal speed 
    
    arg double trav_value:
    ratio of maximum possible speed to be used when
    setting trav_speed to 7. 
    Recommended: 0.3-0.5 if MOTOR_MAX=0.95                          */
void set_traversal_param(double trav_value);

/*  Update parameter for turn speed
    Note that a value greater than 1.0 would allow the wheel-sides 
    to compensate maximum motor-speed by backing, this seemed to 
    caused a dip in power when tested with control-system.
    Using 1.0 means that turn-speed +/-7 slows down one wheel-side
    completely to compensate the breach of MOTOR_MAX limit.

    arg double turn_value:
    ratio of set traversal speed or ratio of trav_speed 7 if robot
    is not moving. 
    RECOMMENDED: 1.0
    DO NOT set to less than TURN_MIN!                               */ 
void set_turn_param(double turn_value);


/*  the "main-loop" of wheel control. Only used for testing so far. 
    intended use: call from the real main-loop of motor-unit.       */
void update_wheel_control();


#endif /* WHEEL_CONTROL_H_ */
