#include "sensor_com.h"

SensorCom::SensorCom(string sensor_interface) : com(sensor_interface) {}

int SensorCom::get_line_center(){
    com.send_msg(GET_LINE_CENTER);
    signed char center = com.read_msg();

    //Cast to get a signed number
    return (int)center;
}

LINE_STATE SensorCom::get_line_state(){
    com.send_msg(GET_LINE_STATE);

    int state = com.read_msg();

    return static_cast<LINE_STATE>(state);
}

pair<bool, bool> SensorCom::get_ware_seen(){

    com.send_msg(GET_WARE_SEEN);
    int answer = com.read_msg();
    bool first = answer >> 1;
    bool second = answer & 0x01;

    return make_pair(first, second);
}

void SensorCom::calibrate_ware(){
    com.send_msg(CALIBRATE_WARE);
}

void SensorCom::calibrate_line(){
    com.send_msg(CALIBRATE_LINE);
}

void SensorCom::calibrate_floor(){
    com.send_msg(CALIBRATE_FLOOR);
}
