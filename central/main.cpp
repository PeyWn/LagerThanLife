/**
    Main file for CentralModule
*/

#include <thread>
#include <iostream>
#include "server_socket.h"
#include "../lib/network/interthreadcom.h"

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

    string msg_read;
    while(true) {
        msg_read = thread_com->read_from_queue(FROM_SOCKET);
        if (msg_read != "") {
            cout << "Msg: " << msg_read << "\n";
        }
    }

    return 0;
}
