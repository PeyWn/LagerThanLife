/**
    Main file for CentralModule
*/
#include <thread>
#include <iostream>
#include <string>
#include "server_socket.h"
#include "../lib/network/interthreadcom.h"
#include "uart_handler.h"
#include "motor_com.h"
#include "sensor_com.h"

using namespace std;

const string SENSOR_INTERFACE = "/dev/ttyUSB0";
const string MOTOR_INTERFACE = "/dev/ttyUSB1";

InterThreadCom* thread_com;
ServerSocket* com_module;

MotorCom motor(MOTOR_INTERFACE);
SensorCom sensor(SENSOR_INTERFACE);

/*

    Function for com_child_new. Checks for new socket connection
    and makes the last connected current connection.
*/
void check_new_connections() {
    while(true) {
        com_module->new_connection();
    }
}

/*
    Function for thread com_child. Starts the main loop in CommunicationModule.
*/
void comm_mod_loop()
{
    com_module = new ServerSocket(thread_com);

    // Spawn a new thread that calls on check_new_connections
    thread com_child_new(check_new_connections);

    com_module->main_loop();
}

/*
    Function for getting the latest updated sensor data.
*/
void get_sensors(int& line_center, LINE_STATE& line_state, pair<bool, bool>& ware_seen){
    line_center = sensor.getLineCenter();
    line_state = sensor.getLineState();
    ware_seen = sensor.getWareSeen();

    string to_user_interface = to_string(line_center) + " " +  to_string(line_state) +
                                " " + to_string(ware_seen.first) + " " +
                                to_string(ware_seen.second);

    thread_com->write_to_queue(to_user_interface, TO_SOCKET);

}

/*
    Function for getting the current robot position.
    Responds with two nodes that the robot currently is inbetween.
*/
void get_pos(){
    //TODO: implement when abstract stock is made
}

/*
    Function for getting the latest calculated rout for the
    robot to drive.
*/
void get_route(){
    //TODO: implement when abstract stock is made
}

/*
    Split up commands that has a parameter
*/
void handle_command_parameter(string msg_with_parameter, string& command, string& parameter){

    /*

        **WARNING**
        untested code

    */

    string delimiter = " ";
    size_t pos = 0;

    pos = ((msg_with_parameter.find(delimiter)) != string::npos);

    if (pos != npos){
        command = msg_with_parameter.substr(0, pos);
        msg_with_parameter.erase(0, pos + delimiter.length());
        parameter = msg_with_parameter;
    }
    else {
        command = msg_with_parameter;
    }
}

/*
    Handles messages recieved from network
    TODO: break out handle_msg() and its help-functions to a new class file  
*/
void handle_msg(string msg) {

    int turn_speed = 3; // 3 by default
    int line_center;
    LINE_STATE line_state;
    pair<bool, bool> ware_seen;
    string command;
    string parameter;

    //TODO test this function
    handle_command_parameter(msg, command, parameter);

    if ( command == "fwd" ) {
        motor.drive(FORWARD);
    }
    else if (command == "drivestop") {
        motor.drive(IDLE);
    }
    else if (command == "right") {
        motor.turn(RIGHT, TURN_SPEED);
    }
    else if (command == "left") {
        motor.turn(LEFT, TURN_SPEED);
    }
    else if (command == "noturn") {
        motor.turn(NONE, TURN_SPEED);
    }
    else if (command == "armright") {
        motor.move_arm(CW);
    }
    else if (command == "armleft") {
        motor.move_arm(CCW);
    }
    else if (command == "armhome") {
        motor.perform_arm_macro(GO_HOME);
    }
    else if (command == "armstop") {
        motor.perform_arm_macro(STOP_ALL);
    }
    else if (command == "pickup") {
        motor.perform_arm_macro(PICK_UP);
    }
    else if (command == "putdown") {
        motor.perform_arm_macro(PUT_DOWN);
    }
    else if (command == "get") {
        // TODO call for get(parameter) fn
    }
    else if (command == "getsensors") {
        get_sensors(line_center, line_state, ware_seen);
    }
    else if (command == "getpos") {
        get_pos();
    }
    else if (command == "getroute") {
        get_route();
    }
    else if (command == "updateall") {
        get_sensors(line_center, line_state, ware_seen);
        get_pos();
        get_route();
    }
    else if (command ==  "auto") {
        //TODO: implement
    }
    else if (command == "manual") {
        //TODO: implement
    }
    else if (command == "armfwd") {
        motor.move_arm(AWAY);
    }
    else if (command == "armback") {
        motor.move_arm(TOWARDS);
    }
    else if (command == "armup") {
        motor.move_arm(UP);
    }
    else if (command == "armdown") {
        motor.move_arm(DOWN);
    }
    else if (command == "closeclaw") {
        motor.control_claw(true);
    }
    else if (command == "openclaw") {
        motor.control_claw(false);
    }
    else if (command == "estop") {
        motor.perform_arm_macro(STOP_ALL);
        motor.drive(IDLE);
        //TODO: more ???
    }
    else if (command == "calware") {
        sensor.calibrateWare();
    }
    else if (command == "calline") {
        sensor.calibrateLine();
    }
    else if (command == "calfloor") {
        sensor.calibrateFloor();
    }
    else if (command == "turnspeed") {
        turn_speed = stoi(parameter);
    }
    else if (command == "empty") {
        // TODO call set stock(parameter) as empty
    }
    else if (command == "refill") {
        // TODO call set stock(parameter) as full
    }
    else if (command == "lager") {
        // TODO send parameter to abst stock to interpet lagerfile
    }
    else if (command == "sethome") {
        // TODO set parameter as home node in abst stock
    }
    else if (command == "showdata") {
        string to_user_interface = to_string(line_center) + " " +  to_string(line_state) +
                                    " " + to_string(ware_seen.first) + " " +
                                    to_string(ware_seen.second);

        thread_com->write_to_queue(to_user_interface, TO_SOCKET);
    }
    else {
        // do nothing
    }

}


int main() {

    // Create a new InterThreadCom used for communication with CommunicationModule
    thread_com = new InterThreadCom();

    // Spawn a new thread that calls on comm_mod_loop
    thread com_child(comm_mod_loop);

    string msg_read;
    while(true) {
        //Netwrok read
        msg_read = thread_com->read_from_queue(FROM_SOCKET);
        if (msg_read != "") {
            // cout << "Msg: " << msg_read << "\n";  //prints the recieved Msg
            handle_msg(msg_read);
        }
    }


    return 0;
}
