#include <thread>
#include <iostream>
#include "command_handler.h"
#include "../lib/network/client_socket.h"
#include "../lib/network/interthreadcom.h"

using namespace std;

const string COMMAND_ERROR = "ERROR! There was an error executing your command.";
InterThreadCom* thread_com;

// Function for thread com_child
void comm_mod_loop()
{
    ClientSocket* com_module = new ClientSocket(thread_com);
    com_module->main_loop();
}

// Function for thread read_child
void read_msg() {
    string msg_read;
    while(true) {
        msg_read = thread_com->read_from_queue(2);
        if (msg_read != "") {
            cout << msg_read << "\n";
        }
    }

}

int main(){
    thread_com = new InterThreadCom();
    CommandHandler cmd_handler(thread_com);

    // Create a new thread to handle communication
    //thread com_child(comm_mod_loop);

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
