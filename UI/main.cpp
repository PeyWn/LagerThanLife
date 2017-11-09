#include <thread>
#include <iostream>
#include "command_handler.h"
#include "client_socket.h"

#include <signal.h>

using namespace std;

const string COMMAND_ERROR = "ERROR! There was an error executing your command.";

InterThreadCom* thread_com;
ClientSocket* com_module;

// Function for thread read_child
void read_msg() {
    string msg_read;
    while(true) {
        msg_read = thread_com->read_from_queue(FROM_SOCKET);
        if (msg_read != "") {
            cout << endl << msg_read << endl << ">";
        }
    }
}

int main(){
    thread_com = new InterThreadCom();
    CommandHandler cmd_handler(thread_com);

    // Create a new thread to handle communication
    com_module = new ClientSocket(thread_com);
    //thread com_child(comm_mod_loop);
    thread com_child([](){com_module->main_loop();});

    // Create a new thread to handle print to console
    thread read_child(read_msg);

    //Main Loop
    while(true){
        cout << "> ";

        string cmd;
        getline(cin, cmd);

        bool cmd_accepted = cmd_handler.try_command(cmd);

        if(!cmd_accepted){
            cout << COMMAND_ERROR << endl;
        }

    }
}
