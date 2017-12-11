#include <iostream>
#include "ware_detection.h"
#include "sensor_com.h"
#include "motor_com.h"
#include <unistd.h>

bool center_ware(pair<bool, bool> sensor, MotorCom* wheels)
{

    int delay_time = 40000; // Used to determine time turning

    if (!(sensor.first && sensor.second))
    {
        wheels->drive(FORWARD, 1);
        if (sensor.first)
        {
            wheels->turn(LEFT, 3);
        }
        else if (sensor.second)
        {
            wheels->turn(RIGHT, 3);
        }
        usleep(delay_time);
        wheels->turn(NONE, 0);
        return false;
    }
    wheels->drive(IDLE, 0);
    return true;

}
