#include "sensor_com.h"

SensorCom::SensorCom(string sensor_interface) : com(sensor_interface) {}

int SensorCom::getLineCenter(){
    com.send_msg(GET_LINE_CENTER);
    int center = com.read_msg();

    return center;
}

LINE_STATE SensorCom::getLineState(){
    com.send_msg(GET_LINE_STATE);
    int state = com.read_msg();

    return static_cast<LINE_STATE>(state);
}

pair<bool, bool> SensorCom::getWareSeen(){
    com.send_msg(GET_WARE_SEEN);
    int answer = com.read_msg();

    bool first = answer >> 1; //bit at position 2
    bool second = answer & 0x01; //lsb

    return make_pair(first, second);
}

void SensorCom::calibrateWare(){
    com.send_msg(CALIBRATE_WARE);
}

void SensorCom::calibrateLine(){
    com.send_msg(CALIBRATE_LINE);
}

void SensorCom::calibrateFloor(){
    com.send_msg(CALIBRATE_FLOOR);
}
