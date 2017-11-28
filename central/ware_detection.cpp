#include <iostream>
#include "ware_detection.h"
#include "sensor_com.h"
#include "motor_com.h"
#include <unistd.h>

void center_ware(pair<bool, bool> sensor, MotorCom wheels, int turn_speed)
{

    // cout << "hej" << endl;
    // //int delay_time = 10000; // Used to determine time turning -- TODO: maybe delete?
    // if (!(sensor.first && sensor.second))
    // {
    //     wheels.drive(FORWARD);
    //     if (sensor.first)
    //     {
    //         wheels.turn(LEFT, turn_speed);
    //     }
    //     else if (sensor.second)
    //     {
    //         wheels.turn(RIGHT, turn_speed);
    //     }
    //     //usleep(delay_time);
    //     wheels.drive(IDLE);
    //     wheels.turn(NONE, turn_speed);
    //     return 0;
    // }
    // return 1;
    do {

        do {
            wheels.drive(FORWARD);
        } while (!(sensor.first || sensor.second))
        wheels.drive(IDLE);

        if (sensor.first) {
            wheels.turn(LEFT, turn_speed);
        }
        else if (sensor.second){
            wheels.turn(RIGHT, turn_speed);
        }
        wheels.turn(NONE, turn_speed);

    } while (!(sensor.first && sensor.second))


}
