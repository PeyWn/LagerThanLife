#ifndef MOTOR_COM_H
#define MOTOR_COM_H

#include <string>
#include <utility>
#include "uart_handler.h"

using namespace std;

//Enums for motor status
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

class MotorCom{
private:
    UARTHandler com;

    enum MOTOR_MSG {
        GET_TURN_STATUS = 0x01,
        GET_DRIVE_STATUS = 0x02,
        GET_ARM_STATUS = 0x0F,

        DRIVE = 0x10,
        TURN = 0x20,

        CONFIGURE_ARM = 0xC0
    };
public:

    MotorCom(string motor_interface);

    DRIVE_STATUS getDriveStatus();

    pair<TURN_STATUS, int> getTurnStatus();

    bool armActive();

    void drive(DRIVE_STATUS direction);

    void turn(TURN_STATUS direction, int speed);

    void setArmSpeed(int speed);
};

#endif /* MOTOR_COM_H */
