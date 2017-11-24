#include <sstream>
#include <iostream>
#include <string>
#include "command_handler.h"

CommandHandler::CommandHandler(InterThreadCom* com) : text_file_handler() {
    robot_com = com;
}

/*
Try to execute given command, return false if can not be done
*/
bool CommandHandler::try_command(string line){
    string cmd;
    stringstream ss;
    ss << line;

    //Load first word into cmd
    ss >> cmd;

    auto cmd_info = acc_cmd.find(cmd);

    if(cmd_info == acc_cmd.end()){
        //Command not found in list of accepted
        return false;
    }

    if(cmd_info->second){
        //Contains more information

        if(
            cmd == "get" ||
            cmd == "sethome" ||
            cmd == "turnspeed"
        ){
            int n;
            ss >> n;

            if(ss.fail()){
                //Could not read an integer
                return false;
            }

            cmd.append(" ");
            cmd.append(to_string(n));
        }
        //TODO implement rest of commands with parameters

        if ( cmd == "lager"){
            //TODO implement read from textfile
            string n;
            ss >> n;
            string filename;
            string lager;

            if(ss.fail()){
                //Coukd not read a string
                return false;
            }

            lager = text_file_handler.read_text_file(n);
            cmd.append(lager); 

        }
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
    robot_com->write_to_queue(msg, TO_SOCKET);
}
