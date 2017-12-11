#include "state_handler.h"
#include <stack>
#include <iostream>

using namespace std;

StateHandler::StateHandler(){}

void StateHandler::interpret_message(string cmd, string param){

    //TODO: implement so that when one of these variables change, it updates the value shown in main_window

    if (cmd == "drivespeed" ) {
        drivespeed = stoi(param);
    }
    else if (cmd == "turnspeed"){
        turnspeed = stoi(param);
    }
    else if (cmd == "getsensors"){
        if (param != ""){
            interpret_sensor_values(param);
        }
    }
    else if (cmd == "getpos"){
        curr_pos = param;
    }
    else if (cmd == "getroute"){
        route = param;
    }
    else if (cmd == "lager"){
        lager = param;
    }
    else {
        //do nothing
    }

}


void StateHandler::interpret_sensor_values(string values){

    stack<string> value_list;
    string delimiter = " ";
    size_t pos = 0;
    string token;

    while ((pos = values.find(delimiter)) != std::string::npos) {
        token = values.substr(0,pos);
        value_list.push(token);
        values.erase(0, pos + delimiter.length());
    }
    value_list.push(values);

    ware_two_value = value_list.top();
    value_list.pop();
    ware_one_value = value_list.top();
    value_list.pop();
    line_sensor_state = value_list.top();
    value_list.pop();
    line_sensor_value = value_list.top();
    value_list.pop();

}

