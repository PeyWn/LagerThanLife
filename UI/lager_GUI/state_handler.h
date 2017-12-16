#ifndef STATE_HANDLER_H
#define STATE_HANDLER_H

#include <string>

using namespace std;

class StateHandler
{
public:
    StateHandler();

    string const NO_VALUE_STRING = "none"; //constant to compare with if state-variables are not set

    string ware_one_value;      //stores the ware sensor 1 value
    string ware_two_value;      //stores the ware sensor 2 value
    string line_sensor_state;   //stores the sensor line state value
    string line_sensor_value;   //stores the line sensor value (between +-127)
    string lager_file;          //stores the current lager string
    string drivespeed;          //stores drivespeed
    string turnspeed;           //stores turnspeed
    string curr_pos;            //stores the current positino (between which two nodes the robot is at)
    string route;               //stores the last calculated route for the robot to go
    string getting_id;          //the last ware that the robot went to get

    /*
     * Function that stores the value we recieve in it's correct variable.
     *
     * string cmd - the command related to the data we recieve
     * string param - the parameter sent with the command that we want to
     * store locally
    */
    void interpret_message(string cmd, string param);

    /*  sets all values of state to "none" */
    void reset();

private:
    /*
     * Function that splits up the string of sensor values in the case of the
     * command "getsensors" and stores them to their respective variables.
     *
     * string values - the string with all four sensor values
    */
    void interpret_sensor_values(string values);

};

#endif // STATE_HANDLER_H
