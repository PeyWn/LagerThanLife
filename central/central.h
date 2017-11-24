#include "../lib/network/interthreadcom.h"
#include "motor_com.h"
#include "sensor_com.h"
#include "control_system.h"
#include <string>

class Central{
private:
    const string SENSOR_INTERFACE = "/dev/ttyUSB0";
    const string MOTOR_INTERFACE = "/dev/ttyUSB1";

    InterThreadCom* thread_com;

    MotorCom motor;
    SensorCom sensor;
    ControlSystem line_follower;
    int turn_speed = 3; // 3 by default

    /*
    Handles messages recieved from network
    */
    void handle_msg(string msg);

    /*
    Split up commands that has a parameter
    */
    void handle_command_parameter(string msg_with_parameter,
                            string& command, string& parameter);

    /*
    Function for getting the latest calculated rout for the
    robot to drive.
    */
    void get_route();

    /*
    Function for getting the current robot position.
    Responds with two nodes that the robot currently is inbetween.
    */
    void get_pos();

    /*
    Function for getting the latest updated sensor data.
    */
    void get_sensors(int& line_center, LINE_STATE& line_state,
                                pair<bool, bool>& ware_seen);
public:
    /*
    Constructor for Central
    */
    Central(InterThreadCom* thread_com_in);


    void main_loop();
};
