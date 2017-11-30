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

//Define to use debug prints
#define DEBUG

using namespace std;

class Central{
private:
    //UART interfaces for motor and sensor units
    const string SENSOR_INTERFACE = "/dev/ttyUSB0";
    const string MOTOR_INTERFACE = "/dev/ttyUSB1";

    //Delay in us between every iteration of mainloop
    const int MAIN_LOOP_DELAY = 10000;

    //Time to drive forward when on a corner
    const double turn_forward_time = 0.6;

    //Turn speed when turning in a corner
    const int CORNER_TURN_SPEED = 6;

    //Turn speed when turning in a corner
    const int AUTO_DRIVE_SPEED = 7;

    //Allowed distance from line after turn to go back to driving
    const int CORNER_LINE_THRESHOLD = 30;

    InterThreadCom* thread_com;

    MotorCom motor;
    SensorCom sensor;

    ControlSystem line_follower;

    int turn_speed = 3; // 3 by default
    int drive_speed = 7; // 7 by default

    //Enum for determining the robots state in autonoumus mode
    enum class RobotState{
        TURN,
        DRIVING,
        PICK_UP,
        DROP_OFF,
        STANDBY
    };

    /*
    State of progree in turning around a corner.

    If the robot is supposed to continue forward after the corner
    the sequence of states would be:

    NEW_TURN -> FORWARD -> (back to driving state)

    Otherwise:
    If there is a line opposite of the one the robot arrives to the corner on
    the sequence of states would be:

    NEW_TURN -> FORWARD -> LEAVING_LINE ->
    BETWEEN_LINES -> (back to driving state)

    If there is no line opposite of the one the robot arrives to the corner on
    the sequence of states would be:

    NEW_TURN -> FORWARD -> BETWEEN_LINES -> (back to driving state)
    */
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
    LineMap* map = nullptr;

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
    Handles commands recieved from the UI. Calls functions in the
    abstract_stock, motor unit and sensor unit.

    string msg - The command recieved from UI.
    */
    void handle_msg(string msg);

    /*
    Split up strings that contain both a command and a parameter into two
    separate strings.

    string msg_with_parameter - Is the command with parameter. The parameter
    will be seen as everytihing after the first  whitespace in
    msg_with_parameter

    string& command - a reference to the string where the command will be
    stored. Is initiated in handle_msg().

    string& parameter - a reference to the string where the paramter will be
    stored. Is initiated in handle_msg().

    */
    void handle_command_parameter(string msg_with_parameter,
                            string& command, string& parameter);

    /*
    Get the latest calculated route for the robot to drive and
    send it to the UI. The route is represented as the IDs of the nodes
    on the path. Example:

    0 4 5 12 13 10 8

    If there is no route calculated only "0" is returned.
    */
    void get_route();

    /*
    Function for getting the current robot position in the
    LineMap and sending it to the UI
    Sends the two nodes that the robot currently is inbetween on the format

    from_id to_id

    If the robot isn't aware of it's position yet it simply sends two zeros.
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

    /*
    Perform action based on sensor values when robot is in the turn state.
    */
    void turn_state();

    /*
    Perform action based on sensor values when robot is in the drive state.
    */
    void drive_state();
public:
    /*
    Constructor for Central
    */
    Central(InterThreadCom* thread_com_in);

    void main_loop();
};

#endif /* CENTRAL_H */
