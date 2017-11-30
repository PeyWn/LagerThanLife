#include "../lib/network/interthreadcom.h"
#include "motor_com.h"
#include "sensor_com.h"
#include "control_system.h"
#include <string>
#include "ware_detection.h"

class Central{
private:
    const string SENSOR_INTERFACE = "/dev/ttyUSB0";
    const string MOTOR_INTERFACE = "/dev/ttyUSB1";
    const double PICK_REVESE_TIME = 0.4;
    
    enum class PickUpState{
	FIND_WARE,
	PICK_UP,
	REVERSE,
	TURN
    };

    
    InterThreadCom* thread_com;

    MotorCom motor;
    SensorCom sensor;
    ControlSystem line_follower;
    int turn_speed = 3; // 3 by default
    int drive_speed = 7; // 7 by default
    int center_flag = 0; // 0 by default
    int line_center;
    LINE_STATE line_state;
    pair<bool, bool> ware_seen;

    PickUpState cur_pick_up_state = PickUpState::FIND_WARE;
    int t_revese = 0;

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
    Function for getting the latest calculated route for the
    robot to drive.
    TODO: update this comment when implementation is made
    */
    void get_route();

    /*
    Function for getting the current robot position.
    Responds with two nodes that the robot currently is inbetween.
    TODO: update this comment when implementation is made
    */
    void get_pos();

    /*
    Function for getting the latest updated sensor data from the sensor unit.
    TODO: update this comment
    */
    void update_sensors(/*int& line_center, LINE_STATE& line_state,
                                pair<bool, bool>& ware_seen*/);
    /*
    Turns line_center, line_state and ware_seen into one string and writes to
    queue (sends to UI over wifi)
    */
    void write_sensors();

    void pick_up();
	
public:
    /*
    Constructor for Central
    */
    Central(InterThreadCom* thread_com_in);


    void main_loop();
};
