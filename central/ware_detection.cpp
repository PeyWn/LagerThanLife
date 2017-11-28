#include <iostream>
#include "ware_detection.h"
#include "sensor_com.h"
#include "motor_com.h"
#include <unistd.h>

int center_ware(pair<bool, bool> sensor, MotorCom wheels, int turn_speed, int drive_speed)
{

    //cout << "hej" << endl;
    int delay_time = 100000; // Used to determine time turning -- TODO: maybe delete?
    if (sensor.first && sensor.second){
	return 1; 
    }
    else if (!(sensor.first && sensor.second))
    {
        wheels.drive(FORWARD, drive_speed);
        if (sensor.first)
        {
            wheels.turn(LEFT, turn_speed);
        }
        else if (sensor.second)
        {
            wheels.turn(RIGHT, turn_speed);
        }
        usleep(delay_time);
        wheels.drive(IDLE, 0);
        wheels.turn(NONE, turn_speed);
        return 0;
    }
    return 1;
    // if (!(sensor.first && sensor.second)) {
    //
    //     if (!(sensor.first || sensor.second)) {
    //         wheels.drive(FORWARD, drive_speed);
    //     }
    //     wheels.drive(IDLE, 0);
    //
    //     while (sensor.first) {
    //         wheels.turn(LEFT, turn_speed);
    //     }
    //     while (sensor.second){
    //         wheels.turn(RIGHT, turn_speed);
    //     }
    //     wheels.turn(NONE, turn_speed);
    // }


}
