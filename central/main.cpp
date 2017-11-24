<<<<<<< HEAD
#include "central.h"
#include "../lib/network/interthreadcom.h"
#include "server_socket.h"
#include <thread>
=======
/**
    Main file for CentralModule
*/
#include <thread>
#include <string>
#include <iostream>
#include "server_socket.h"
#include "../lib/network/interthreadcom.h"
#include "uart_handler.h"
#include "motor_com.h"
#include "sensor_com.h"
#include "control_system.h"

using namespace std;

const string SENSOR_INTERFACE = "/dev/ttyUSB0";
const string MOTOR_INTERFACE = "/dev/ttyUSB1";
>>>>>>> master

ServerSocket* com_module;

<<<<<<< HEAD
=======
MotorCom 		motor(MOTOR_INTERFACE);
SensorCom 		sensor(SENSOR_INTERFACE);
ControlSystem	line_follow(&sensor, &motor);	//control system for line following


>>>>>>> master
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
    com_module->main_loop();
}

int main(){
    InterThreadCom* thread_com = new InterThreadCom();

    // Spawn a new thread that calls on comm_mod_loop
    com_module = new ServerSocket(thread_com);
    thread com_child(comm_mod_loop);

<<<<<<< HEAD
    // Spawn a new thread that calls on check_new_connections
    thread com_child_new(check_new_connections);
=======
    string msg_read;
    while(true) {
        //Netwrok read
        msg_read = thread_com->read_from_queue(FROM_SOCKET);
        if (msg_read != "") {
            cout << "Msg: " << msg_read << "\n";
        }

	// control system testing
	line_follow.run();
	
        // Motor com testing
	/*
	motor.turn(RIGHT, 7);
	auto status = motor.get_turn_status();
        cout << "Turn status: " << status.first << " " << status.second << endl;
	*/
    }
>>>>>>> master

    Central central_unit(thread_com);
    central_unit.main_loop();
}
