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

void handle_msg(string msg) {
    //const int TURN_SPEED = 3; //TODO: implement variation of turn speed
    int line_center;
    LINE_STATE line_state;
    pair<bool, bool> ware_seen;

    if ( msg == "fwd" ) {
        motor.drive(FORWARD);
    }
    else if (msg == "drivestop") {
        motor.drive(IDLE);
    }
    else if (msg == "right") {
        motor.turn(RIGHT, TURN_SPEED);
    }
    else if (msg == "left") {
        motor.turn(LEFT, TURN_SPEED);
    }
    else if (msg == "noturn") {
        motor.turn(NONE, TURN_SPEED);
    }
    else if (msg == "armright") {
        motor.move_arm(CW);
    }
    else if (msg == "armleft") {
        motor.move_arm(CCW);
    }
    else if (msg == "armhome") {
        motor.perform_arm_macro(GO_HOME);
    }
    else if (msg == "armstop") {
        motor.perform_arm_macro(STOP_ALL);
    }
    else if (msg == "pickup") {
        motor.perform_arm_macro(PICK_UP);
    }
    else if (msg == "putdown") {
        motor.perform_arm_macro(PUT_DOWN);
    }
    else if (msg == "getsensors") {
        get_sensors(line_center, line_state, ware_seen);
    }
    else if (msg == "getpos") {
        get_pos();
    }
    else if (msg == "getroute") {
        get_route();
    }
    else if (msg == "updateall") {
        get_sensors(line_center, line_state, ware_seen);
        get_pos();
        get_route();
    }
    else if (msg ==  "auto") {
        //TODO: implement
    }
    else if (msg == "manual") {
        //TODO: implement
    }
    else if (msg == "armfwd") {
        motor.move_arm(AWAY);
    }
    else if (msg == "armback") {
        motor.move_arm(TOWARDS);
    }
    else if (msg == "armup") {
        motor.move_arm(UP);
    }
    else if (msg == "armdown") {
        motor.move_arm(DOWN);
    }
    else if (msg == "closeclaw") {
        motor.control_claw(true);
    }
    else if (msg == "openclaw") {
        motor.control_claw(false);
    }
    else if (msg == "estop") {
        motor.perform_arm_macro(STOP_ALL);
        motor.drive(IDLE);
        //TODO: more ???
    }
    else if (msg == "calware") {
        sensor.calibrateWare();
    }
    else if (msg == "calline") {
        sensor.calibrateLine();
    }
    else if (msg == "calfloor") {
        sensor.calibrateFloor();
    }

    /*
    TODO: when abstract stock is done, implement the following commands:
    See table 6.3 in technical doc. for a desciption

    1. empty [id] : implement when abstract stock is made
    2. refill [id] : implement when abstract stock is made
    4. lager [filnamn] : implement when abstract stock is made
    5. sethome [id] : implement when abstract stock is made

    see table 6.2 for the following command
    12. get [id] implement when abstract stock is made
    29. turnspeed [int]

    */

    else if (msg == "showdata") {
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
