#ifndef STATE_HANDLER_H
#define STATE_HANDLER_H

class state_handler
{
public:
    state_handler();

    int ware_one_value;
    int ware_two_value;
    int line_sensor_state;
    int line_sensor_value;
    string lager; //stores the current lager for drawing it
    int drivespeed;
    int turnspeed;
    string drive_status;
    string turn_status;


};

#endif // STATE_HANDLER_H
