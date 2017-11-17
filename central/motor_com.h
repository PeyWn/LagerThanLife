#ifndef MOTOR_COM_H
#define MOTOR_COM_H

#include <string>
#include <utility>
#include "uart_handler.h"

using namespace std;

//Enums for motor status and commands
enum DRIVE_STATUS {
    IDLE = 0,
    FORWARD = 1,
    BACKWARDS = 2
};

enum TURN_STATUS {
    NONE,
    RIGHT,
    LEFT
};

enum ARM_MACRO{
    STOP_ALL = 0,
    GO_GOME = 1,
    PICK_UP = 2,
    PUT_DOWN = 3
};

enum ARM_DIRECTION{
    CW = 0,
    CCW = 2,
    UP = 4,
    DOWN = 6,
    TOWARDS = 8,
    AWAY = 10
};

class MotorCom{
private:
    UARTHandler com;

    //Part of messages for communnication with motor unit
    const int GET_TURN_STATUS = 0x01;
    const int GET_DRIVE_STATUS = 0x02;
    const int GET_ARM_STATUS = 0x0F;
    const int DRIVE = 0x10;
    const int TURN = 0x20;
    const int CONFIGURE_ARM = 0xC0;
    const int ARM_PERFROM_MACRO = 0xE0;
    const int MANUAL_ARM_CONTROL = 0xF0;
    const int CONTROL_CLAW = 0xD0;
public:

    /*
    Create a new MotorCom that communicates with the
    motor unit over the given interface

    motor_interface - the interface to use for uart communication
    */
    MotorCom(string motor_interface);

    /*
    Get the driving status of the motor unit

    return - if the robot is driving and in which direction,
            all contained in a DRIVE_STATUS value
    */
    DRIVE_STATUS get_drive_status();

    /*
    Get the turning status of the motor unit

    return - a pair where the first variable is which direction the
            motor unit is currently turning in and the second variable with
            which speed it it turning (on a scale 1-7).
    */
    pair<TURN_STATUS, int> get_turn_status();

    /*
    Get wheter the arm is active moving or not

    return - true if the arm is actively moving, false otherwise
    */
    bool arm_active();

    /*
    Tell the motor unit to drive in the given direction, or stop.
    If the direction is idle the motor unit stops.

    direction - The direction the robot should drive in.
    */
    void drive(DRIVE_STATUS direction);

    /*
    Tell the motor unit to turn in a direction with a given speed.

    direction - The direction to start turning in.
                Stops turning if direction is none.
    speed - The speed to use when turning, on a scale 1-7.
    */
    void turn(TURN_STATUS direction, int speed);

    /*
    Set the speed for the arm to move with.

    speed - the speed for arm movement, on a scale 1-15.
    */
    void set_arm_speed(int speed);

    /*
    Perform a predefined arm macro. Move to a position or
    send some message to all arm motors.
    See ARM_MACRO for different macros available.

    move - The macro to perform.
    */
    void perform_arm_macro(ARM_MACRO move);

    /*
    Open or close the claw on the robot arm.

    close - if true closes the claw, otherwise opens it.
    */
    void control_claw(bool close);

    /*
    Start moving the arm in the given direction.

    direction - the direction to tell the motor unit to move the arm.
    */
    void move_arm(ARM_DIRECTION direction);

    /*
    Stops movement of the arm in the given direction.

    direction - the arm direction to stop movement in.
    */
    void stop_arm(ARM_DIRECTION direction);
};

#endif /* MOTOR_COM_H */
