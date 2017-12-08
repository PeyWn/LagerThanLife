#ifndef STATE_HANDLER_H
#define STATE_HANDLER_H

#include <string>

using namespace std;

class StateHandler
{
public:
    StateHandler();

    string ware_one_value = "hacker";
    string ware_two_value = "jocke";
    string line_sensor_state = "was"; //9000 for testing right now
    string line_sensor_value = "here";
    string lager; //stores the current lager for drawing it
    string drivespeed;
    string turnspeed;
    string drive_status;
    string turn_status;
    string curr_pos;
    string route;

    void interpret_message(string cmd, string param);

private:
    void split_msg(string msg_with_parameter, string& command, string& answer);
    void interpret_sensor_values(string values);

};

#endif // STATE_HANDLER_H
