#include <sstream>
#include <iostream>
#include <string>
#include "command_handler.h"
#include <unistd.h>


CommandHandler::CommandHandler(InterThreadCom* com, StateHandler* state, ClientSocket* socket) : text_file_handler("") {
    robot_com = com;
    state_handler = state;
    com_socket = socket;
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

    //saves the command-part to later see if the command get answers back from robot
    string ask_cmd = cmd;

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
            cmd == "turnspeed" ||
            cmd == "drivespeed"
        ){
            int n;
            ss >> n;

            if(ss.fail()){
                //Could not read an integer
                return false;
            }


            cmd.append(" ");
            cmd.append(to_string(n));

            // TODO: implement update state_handler <---------------------------
            // state_handler->interpret_result(ask_cmd, n); <---------------------------
            state_handler->interpret_message(ask_cmd, to_string(n));
        }

        if ( cmd == "lager"){
            string filename;
            ss >> filename;
            //string filename;
            string lager;

            if(ss.fail()){
                //Could not read a string
                return false;
            }

            lager = text_file_handler.read_text_file(filename);
            cmd.append(lager);

            // TODO: implement update state_handler <---------------------------
            // state_handler->interpret_result(ask_cmd, lager); <---------------------------
            state_handler->interpret_message("lager", lager);
        }
    }

    //send command to robot
    send_msg(cmd);

    //if there is a command where we expect to get an answer, read it and send to state_handler
    if(  //cmd == updateall ????? tar emot 3 meddelanden
        ask_cmd == "getsensors" ||
        ask_cmd == "getpos" ||
        ask_cmd == "getroute"
    ){

        string param = read_msg();

        if(param != ""){
            state_handler->interpret_message(ask_cmd, param);
        }
    }

        return true;
}

/*
Read the last message recieved to the network module for communication to the robot
*/
string CommandHandler::read_msg(){
    //busy wait till det finns något att läsa ???? <<<<--------------- how!
    string answer = "";

    while(answer == "" && com_socket->is_connected()){
        answer = robot_com->read_from_queue(FROM_SOCKET);
    }

    return answer;
}


/*
Send the given string to the network module for communication to the robot

msg - the string to be sent
*/
void CommandHandler::send_msg(string msg){
    robot_com->write_to_queue(msg, TO_SOCKET);
}
