/**
    Main file for CentralModule
*/

#include <thread>
#include <iostream>
#include "../lib/server_socket.h"
#include "../lib/interthreadcom.h"

using namespace std;

InterThreadCom* thread_com;

/*
    Function for thread com_child. Starts the main loop in CommunicationModule.
*/
void comm_mod_loop()
{
    ServerSocket* com_module = new ServerSocket(thread_com);
    com_module->main_loop();
}

int main() {

    thread_com = new InterThreadCom();  // Create a new InterThreadCom used for communication with CommunicationModule

    thread com_child(comm_mod_loop);   // Spawn a new thread that calls on function comm_mod_loop

    string msg_read;
    while(true) {
        msg_read = thread_com->read_from_queue(2);
        if (msg_read != "") {
            cout << "Msg: " << msg_read << "\n";

            thread_com->write_to_queue("I got the message thank you", 1);
            thread_com->write_to_queue("thank you again", 1);
        }

    }

    // com_child.join();

    return 0;
}