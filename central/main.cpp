/**
    Main file for CentralModule
*/

#include <thread>
#include <iostream>
#include "server_socket.h"
#include "../lib/network/interthreadcom.h"
#include "uart_handler.h"

using namespace std;

InterThreadCom* thread_com;
ServerSocket* com_module;

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

int main() {
    // Create a new InterThreadCom used for communication with CommunicationModule
    thread_com = new InterThreadCom();

    // Spawn a new thread that calls on comm_mod_loop
    thread com_child(comm_mod_loop);

    //Set up uart
    UARTHandler uart("/dev/ttyUSB0");

    string msg_read;
    while(true) {
        //Netwrok read
        msg_read = thread_com->read_from_queue(FROM_SOCKET);
        if (msg_read != "") {
            cout << "Msg: " << msg_read << "\n";
        }

        //UART
        //Send test message
	for(int i = 0; i < 255; i++){
	  uart.send_msg(i);

	  uart_msg buffer[255];
	  while(!uart.read_msg(buffer)){
	    
	  }

	  cout << "Read:" << (int)buffer[0] << endl;
	}
    }

    return 0;
}
