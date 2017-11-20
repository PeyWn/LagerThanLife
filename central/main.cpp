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
    cout << "line_state: " << line state << endl;
    cout << "ware 0: " << ware_seen[0] << endl;
    cout << "ware 1: " << ware_seen[1] << endl;
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
    switch(msg) {
        default: {
            break;
        }
        case fwd: {
            motor.drive(FORWARD);
            break;
        }
        case stop: {
            motor.drive(IDLE);
            break;
        }
        case right: {
            const int TURN_SPEED = 3; //TODO: implement variation of turn speed
            motor.turn(RIGHT, TURN_SPEED);
            break;
        }
        case left: {
            const int TURN_SPEED = 3; //TODO: implement variation of turn speed
            motor.turn(LEFT, TURN_SPEED);
            break;
        }
        case noturn: {
            motor.turn(NONE);
            break;
        }
        case armright: {
            motor.move_arm(CW);
            break;
        }
        case armleft: {
            motor.move_arm(CCW);
            break;
        }
        case armstop: {
            motor.perform_arm_macro(STOP_ALL);
            break;
        }
        case pickup: {
            motor.perform_arm_macro(PICK_UP);
            break;
        }
        case putdown: {
            motor.perform_arm_macro(PUT_DOWN);
            break;
        }
        // case get [id] ??

        case getsensors: {
            get_sensors();
            break;
        }
        case getpos: {
            get_pos();
            break;
        }
        case getroute: {
            get_route();
            break;
        }
        case updateall: {
            get_sensors();
            get_pos();
            get_route();
            break;
        }
        case auto: {
            //behövs denna?
            break;
        }
        case manual: {
            //behövs denna?
            break;
        }
        case armfwd: {
            motor.move_arm(AWAY);
            break;
        }
        case armback: {
            motor.move_arm(TOWARDS);
            break;
        }
        case armup: {
            motor.move_arm(UP);
            break;
        }
        case armdown: {
            motor.move_arm(DOWN);
            break;
        }
        case closeclaw: {
            control_claw(true);
            break;
        }
        case openclaw: {
            control_claw(false);
            break;
        }
        case rotgrip: {
            //how?
            break;
        }
        case estop: {
            motor.perform_arm_macro(STOP_ALL);
            motor.drive(IDLE);
            //more ???
            break;
        }
        case calware: {
            sensor.calibrateWare();
            break;
        }
        case calline: {
            sensor.calibrateLine();
            break;
        }
        case calfloor: {
            sensor.calibrateFloor();
            break;
        }
        //case empty [id] : implement when abstract stock is made
        //case refill [id] : implement when abstract stock is made
        //case lager [filnamn] : implement when abstract stock is made
        //case sethome [id] : implement when abstract stock is made
        //case showdata
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
            handle_msg(msg);
        }
    }


    return 0;
}
