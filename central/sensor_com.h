#ifndef SENDOR_COM_H
#define SENDOR_COM_H

#include "uart_handler.h"
#include <utility>
#include <string>

using namespace std;

//States of the line sensor
enum LINE_STATE {NONE_DOUBLE, SINGLE, CORNER};

class SensorCom{
private:
    UARTHandler com;

    //Lookup for messages to send to sensor unit
    enum SENSOR_MSG {
        GET_LINE_CENTER = 1,
        GET_LINE_STATE = 2,
        GET_WARE_SEEN = 3,
        CALIBRATE_WARE = 4,
        CALIBRATE_LINE = 5,
        CALIBRATE_FLOOR = 6
    };
public:
    SensorCom(string sensor_interface);

    int getLineCenter();

    LINE_STATE getLineState();

    pair<bool, bool> getWareSeen();

    void calibrateWare();

    void calibrateLine();

    void calibrateFloor();
};

#endif /* SENDOR_COM_H */
