#ifndef CENTRAL_H
#define CENTRAL_H

#include "../lib/network/interthreadcom.h"
#include "motor_com.h"
#include "sensor_com.h"
#include "control_system.h"
#include "../lib/abstract_stock/line_map.h"
#include "../lib/abstract_stock/line_node.h"
#include "../lib/abstract_stock/line.h"
#include <string>
#include <stack>
#include <time.h>

using namespace std;

class Central{
private:
    //UART interfaces for motor and sensor units
    const string SENSOR_INTERFACE = "/dev/ttyUSB0";
    const string MOTOR_INTERFACE = "/dev/ttyUSB1";

    //Time to drive forward when on a corner
    const double turn_forward_time = 1;

    //Turn speed when turning in a corner
    const int corner_turn_speed = 3;

    InterThreadCom* thread_com;

    MotorCom motor;
    SensorCom sensor;

    ControlSystem line_follower;

    int turn_speed = 3; // 3 by default

    //Enum for determining the robots state in autonoumus mode
    enum class RobotState{
        TURN,
        DRIVING,
        PICK_UP,
        DROP_OFF,
        STANDBY
    };

    enum class TurnState{
        NEW_TURN,
        FORWARD,
        LEAVING_LINE,
        BETWEEN_LINES
    };

    //Current state of the robot
    RobotState state = RobotState::STANDBY;

    //Is robot in manual mode
    bool manual = false;

    //Map of the current area
    LineMap* map;

    //Id of the node to leave wares at
    int home_id = 0;

    //State while driving
    Line* cur_line = nullptr;
    LineNode* next_node = nullptr;
    stack<Line*> cur_path;

    //Buffered sensor values
    int line_center;
    LINE_STATE line_state;
    pair<bool, bool> ware_seen;

    //Information when performing a turn
    int turn_angle; //Angle for current turn, multiple of (pi/2)
    TurnState cur_turn_state;
    clock_t clock_start;


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
    Send sensor information to UI
    */
    void transmit_sensors();

    /*
    Function for getting the latest updated sensor data.
    */
    void update_sensors();
public:
    /*
    Constructor for Central
    */
    Central(InterThreadCom* thread_com_in);

    void main_loop();
};

#endif /* CENTRAL_H */
