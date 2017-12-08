#include "state_handler.h"

StateHandler::StateHandler(){}

void StateHandler::interpret_message(string msg){
    string command;
    string answer;

    split_msg(msg, command, answer);

    if (command == "drivespeed" ) {
        drivespeed = stoi(answer);
    }
        //drivespeed
        //turnspeed
        //getsensors
        //getpos
        //get route

}

void StateHandler::split_msg(string msg_with_parameter,
    string& command, string& answer){

    string delimiter = " ";
    size_t pos = 0;

    pos = msg_with_parameter.substr(0,
            msg_with_parameter.find_first_of(" ")).length();

    if (pos > 0){
        command = msg_with_parameter.substr(0, pos);
        msg_with_parameter.erase(0, pos + delimiter.length());
        answer = msg_with_parameter;
    }
    else {
        command = msg_with_parameter;
    }
}
