#ifndef MOTOR_COM_H
#define MOTOR_COM_H

#include <string>
#include "uart_handler.h"

class MotorCom{
private:
    UARTHandler com;
public:
    MotorCom(string motor_interface);

};

#endif /* MOTOR_COM_H */
