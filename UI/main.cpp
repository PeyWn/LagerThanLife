#include <thread>
#include <iostream>
//#include "CommandHandler.h"
#include "../lib/client_socket.h"
#include "../lib/interthreadcom.h"

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
    //CommandHandler cmd_handler;

    thread_com = new InterThreadCom();
    thread com_child(comm_mod_loop); // Create a new thread to handle communication

    thread read_child(read_msg); // Create a new thread to handle print to console

    string msg_write;
    //Main Loop
    while(true){
        /*cout << "> ";

        string cmd;
        cin >> cmd;

        bool cmd_accepted = cmd_handler.try_command(cmd);

        if(!cmd_accepted){
            cout << COMMAND_ERROR << endl;
        }
        */
        cout << "Enter a message: ";
        getline(cin, msg_write);
        thread_com->write_to_queue(msg_write, 1);


    }
}
