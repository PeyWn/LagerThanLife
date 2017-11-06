#include <sstream>
#include <iostream>
#include <string>
#include "CommandHandler.h"

CommandHandler::CommandHandler(){}

/*
Try to execute given command, return false if can not be done
*/
bool CommandHandler::try_command(string line){
    string cmd;
    stringstream ss;
    ss << line;

    //Load first word into cmd
    ss >> cmd;

    //cout << "command: " << cmd <<endl;
    auto cmd_info = acc_cmd.find(cmd);

    if(cmd_info == acc_cmd.end()){
        //Command not found in list of accepted
        return false;
    }

    if(cmd_info->second){
        //Contains more information

        if(
            cmd == "get" ||
            cmd == "setome"
        ){
            int n;
            ss >> n;

            if(ss.fail()){
                //Could not read an integer
                return false;
            }

            cmd.append(" ");
            cmd.append(to_string(n));

            send_msg(cmd);
        }
        //TODO implement rest of commands with parameters
    }

    //send command to robot
    send_msg(cmd);
    return true;
}

/*
Send the given string to the network module for communication to the robot

msg - the string to be sent
*/
void CommandHandler::send_msg(string msg){
    //TODO implement this
    //for now, just print
    cout << "To Robot: " << msg << endl;
}
