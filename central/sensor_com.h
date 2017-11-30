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

    /*
    Create a new sensor com object that talks to the given interface.

    sensor_interface - the uart interface to use for
                        communication with the sensor unit.
    */
    SensorCom(string sensor_interface);

    /*
    Get the position of the line under the line sensor from the sensor unit.

    return - The position of the line, between -127 (right) and 127 (left).
    */
    int get_line_center();

    /*
    Get the line state registered by the sensor unit.

    return - the current line state.
    */
    LINE_STATE get_line_state();

    /*
    Get if the ware sensors register wares in front of them.

    return - a pair of booleans that tell wheter the ware sensors
            detect a ware in front of them. The first value is the right sensor
            and the second one the left sensor.
    */
    pair<bool, bool> get_ware_seen();

    /*
    Tell the sensor unit to calibrate the ware sensors.
    */
    void calibrate_ware();

    /*
    Tell the sensor unit to calibrate the line sensor
    as if the robot is on a line.
    */
    void calibrate_line();

    /*
    Tell the sensor unit to calibrate the line sensor
    as if the robot is not on a line (on the floor).
    */
    void calibrate_floor();
};

#endif /* SENDOR_COM_H */
