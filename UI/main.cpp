#include <iostream>
#include "CommandHandler.h"

using namespace std;


const string COMMAND_ERROR = "ERROR! There was an error executing your command.";
int main(){
    CommandHandler cmd_handler;

    //Main Loop
    while(true){
        cout << "> ";

        string cmd;
        cin >> cmd;

        bool cmd_accepted = cmd_handler.try_command(cmd);

        if(!cmd_accepted){
            cout << COMMAND_ERROR << endl;
        }
    }
}
