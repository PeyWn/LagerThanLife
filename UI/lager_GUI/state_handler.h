#ifndef STATE_HANDLER_H
#define STATE_HANDLER_H

#include <string>

using namespace std;

class StateHandler
{
public:
    StateHandler();

    int ware_one_value;
    int ware_two_value;
    int line_sensor_state;
    int line_sensor_value;
    string lager; //stores the current lager for drawing it
    int drivespeed;
    int turnspeed;
    string drive_status;
    string turn_status;

    void interpret_message(string msg);
    void split_msg(string msg_with_parameter, string& command, string& answer);

};

#endif // STATE_HANDLER_H
