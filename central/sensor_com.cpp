#include "sensor_com.h"

SensorCom::SensorCom(string sensor_interface) : com(sensor_interface) {}

int SensorCom::get_line_center(){
    com.send_msg(GET_LINE_CENTER);
    signed char center = com.read_msg();

    //Fix to get a signed number
    return (int)center;
}

LINE_STATE SensorCom::get_line_state(){
    clock_t clk = clock();
    com.send_msg(GET_LINE_STATE);

    clock_t clk1 = clock();
    double clk_send = (float)(clk1 - clk)/CLOCKS_PER_SEC;
    
    int state = com.read_msg();

    double clk_read = (float)(clock() - clk1)/CLOCKS_PER_SEC;

    printf("Time to UART SEND message : %f\n", clk_send);
    printf("Time to UART READ message : %f\n", clk_read);

    return static_cast<LINE_STATE>(state);
}

pair<bool, bool> SensorCom::get_ware_seen(){
    com.send_msg(GET_WARE_SEEN);
    int answer = com.read_msg();

    bool first = answer >> 1; //bit at position 2
    bool second = answer & 0x01; //lsb

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
