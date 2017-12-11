#ifndef WHEEL_CONTROL_H_
#define WHEEL_CONTROL_H_
#include <avr/io.h>

/* max speeds: +/- interval for possible integer settings                                       */
#define MAX_TRAV_SETTING 7  // traversal speed settings
#define MAX_TURN_SETTING 7  // turn speed settings

/*  initial setup for wheel control when AVR-unit is started
    . sets registers that need to be set
    . enables PWM pins
    . enables DIR1 and DIR2 pins
    . set speeds to 0                                                                           */
int init_wheel_control();

/*  get current traversal speed

    return:
    current speed -MAX_TRAV_SETTING...+MAX_TRAV_SETTING (int)                                   */
int get_traversal_status();

/* return the current turn speed */
int get_turn_status();

/*  set a new speed for moving robot forward/backward or stop. Front of robot is based on where
    sensors are placed. Traversal speed is saturated at MAX_TRAV_SETTING constant. PWM output is
    safely restricted from above by MOTOR_MAX.

    arg int trav_value :
    the new traversal value for moving the robot forward and backward. Values explained:
    +1 ...  MAX_TRAV_SETTING  -> forward
     0                        -> stop
    -1 ... -MAX_TRAV_SETTING  -> backward                                                       */
void set_traversal_speed(int trav_value);


/*  set new turning speed for robot rotation. Rotation is based on current traversal speed such
    that the robot will maintain same traversal movement when rotating. The rotation is scaled
    by the TURN_MAX constant and restricted by the MOTOR_MAX constant. Turn-speed is alse
    saturated at MAX_TURN_SETTING constant.

    arg int turn_value:
    the new turn speed setting. Can be set to any integer
    value in the interval +/-MAX_TURN_SETTING where positive is right turn
    and 0 is no turning.                                                                        */
void set_turn_speed(int turn_value);

/*  set parameter trav_max for traversal speed
    Max speed of traversal movement. The current traversal speed is scaled by this factor. When
    turn speed is greater than traversal speed, the slower wheel will switch
    direction.

    arg double turn_value:
    The value corresponding to a traversal speed of MAX_TRAV_SETTING. It is a ratio of
    MOTOR_MAX in wheel_control.c.                                                               */
void set_traversal_param(double trav_value);

/*  set parameter turn_max for turn speed
    Max speeds of turn and traversal movement. The current speeds are scaled by this factor. PWM
    output is restricted from above by MOTOR_MAX. TURN_MIN and TURN_MIN_MOVING corresponds to
    the lowest turn speed setting 1 with no traversal speed and with traversal speed
    respectively. When turn speed is greater than traversal speed, the slower wheel will switch
    direction.

    arg double turn_value:
    The value corresponding to a turn speed of MAX_TURN_SETTING. It is a ratio of MOTOR_MAX in
    wheel_control.c.                                                                            */
void set_turn_param(double turn_value);


/*  the "main-loop" of wheel control. Only used for testing so far. intended use: call from the
    real main-loop of motor-unit.                                                               */
void update_wheel_control();

#endif /* WHEEL_CONTROL_H_ */
