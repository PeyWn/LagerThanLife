#include <iostream>
#include "ware_detection.h"
#include "sensor_com.h"
#include "motor_com.h"
#include <dos.h>

int center_ware(pair<bool, bool> sensor, MotorCom wheels, int turn_speed)
{
    int delay_time = 10; // Used to determine time turning
    if (!(sensor.first && sensor.second))
    {
        wheels.drive(FORWARD);
        if (sensor.first)
        {
            wheels.turn(LEFT, turn_speed);
        }
        else if (!(sensor.second))
        {
            wheels.turn(RIGHT, turn_speed);
        }
        delay(delay_time);
        wheels.drive(IDLE);
        return 0;
    }
    return 1;
}
