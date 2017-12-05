#include "central.h"
#include "../lib/network/interthreadcom.h"
#include "server_socket.h"
#include <thread>

ServerSocket* com_module;
InterThreadCom* thread_com;

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

int main(){
    thread_com = new InterThreadCom();

    // Spawn a new thread that calls on comm_mod_loop
    thread com_child(comm_mod_loop);

    Central central_unit(thread_com);
    central_unit.main_loop();
}
