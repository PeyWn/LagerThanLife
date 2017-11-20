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
void get_sensors(){
    int line_center = sensor.getLineCenter();
    LINE_STATE line_state = sensor.getLineState();
    pair<bool, bool> ware_seen = sensor.getWareSeen();

    cout << "line center: " << line_center << endl;
    cout << "line_state: " << line_state << endl;
    cout << "ware 0: " << ware_seen.first << endl;
    cout << "ware 1: " << ware_seen.second << endl;
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

        if ( msg == "fwd" ) {
            motor.drive(FORWARD);
        }
        else if (msg == "stop") {
            motor.drive(IDLE);
        }
        else if (msg == "right") {
            const int TURN_SPEED = 3; //TODO: implement variation of turn speed
            motor.turn(RIGHT, TURN_SPEED);
        }
        else if (msg == "left") {
            const int TURN_SPEED = 3; //TODO: implement variation of turn speed
            motor.turn(LEFT, TURN_SPEED);
        }
        else if (msg == "noturn") {
            motor.perform_arm_macro(STOP_ALL);
        }
        else if (msg == "armright") {
            motor.move_arm(CW);
        }
        else if (msg == "armleft") {
            motor.move_arm(CCW);
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
        // case get [id] ??

        else if (msg == "getsensors") {
            get_sensors();
        }
        else if (msg == "getpos") {
            get_pos();
        }
        else if (msg == "getroute") {
            get_route();
        }
        else if (msg == "updateall") {
            get_sensors();
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
        else if (msg == "rotclaw") {
            //how?
        }
        else if (msg == "estop") {
            motor.perform_arm_macro(STOP_ALL);
            motor.drive(IDLE);
            //more ???
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
        else {
            // do nothing
        }

        //case empty [id] : implement when abstract stock is made
        //case refill [id] : implement when abstract stock is made
        //case lager [filnamn] : implement when abstract stock is made
        //case sethome [id] : implement when abstract stock is made
        //case showdata

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
