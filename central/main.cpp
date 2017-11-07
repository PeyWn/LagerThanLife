/**
    Main file for CentralModule
*/

#include <thread>
#include <iostream>
#include "../lib/network/server_socket.h"
#include "../lib/network/interthreadcom.h"

using namespace std;

InterThreadCom* thread_com;
ServerSocket* com_module;

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

int main() {

    thread_com = new InterThreadCom();  // Create a new InterThreadCom used for communication with CommunicationModule
    com_module = new ServerSocket(thread_com);

    thread com_child(comm_mod_loop);   // Spawn a new thread that calls on function comm_mod_loop
    thread com_child_new(check_new_connections);

    string msg_read;
    while(true) {
        msg_read = thread_com->read_from_queue(2);
        if (msg_read != "") {
            cout << "Msg: " << msg_read << "\n";

            thread_com->write_to_queue("I got the message thank you", 1);
        }

    }

    // com_child.join();

    return 0;
}
