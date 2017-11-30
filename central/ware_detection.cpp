#include <iostream>
#include "ware_detection.h"
#include "sensor_com.h"
#include "motor_com.h"
#include <unistd.h>

int center_ware(pair<bool, bool> sensor, MotorCom* wheels)
{

    int delay_time = 100000; // Used to determine time turning

    if (!(sensor.first && sensor.second))
    {
        wheels->drive(FORWARD, 3);
        if (sensor.first)
        {
            wheels->turn(LEFT, 1);
        }
        else if (sensor.second)
        {
            wheels->turn(RIGHT, 1);
        }
        usleep(delay_time);
        wheels->turn(NONE, 1);
        return 0;
    }
    wheels->drive(IDLE, 0);
    return 1;

}
