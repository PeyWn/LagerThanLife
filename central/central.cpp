#include "central.h"
#include <iostream>

using namespace std;

Central::Central(InterThreadCom* thread_com_in) : motor(MOTOR_INTERFACE),
         sensor(SENSOR_INTERFACE),  thread_com(thread_com_in),
         line_follower(&sensor, &motor) {}

void Central::transmit_sensors(){
    string to_user_interface = to_string(line_center) + " " +  to_string(line_state) +
                                " " + to_string(ware_seen.first) + " " +
                                to_string(ware_seen.second);

    thread_com->write_to_queue(to_user_interface, TO_SOCKET);
}

void Central::update_sensors(){
    line_center = sensor.getLineCenter();
    line_state = sensor.getLineState();
    ware_seen = sensor.getWareSeen();
}

void Central::get_pos(){
    //TODO: implement when abstract stock is made
}


void Central::get_route(){
    //TODO: implement when abstract stock is made
}

void Central::handle_command_parameter(string msg_with_parameter, string& command, string& parameter){

    string delimiter = " ";
    size_t pos = 0;

    pos = msg_with_parameter.substr(0,msg_with_parameter.find_first_of(" ")).length();

    if (pos > 0){
        command = msg_with_parameter.substr(0, pos);
        msg_with_parameter.erase(0, pos + delimiter.length());
        parameter = msg_with_parameter;
    }
    else {
        command = msg_with_parameter;
    }
}

void Central::handle_msg(string msg) {
    int line_center;
    LINE_STATE line_state;
    pair<bool, bool> ware_seen;
    string command;
    string parameter;

    handle_command_parameter(msg, command, parameter);

    if(manual){
        //Only allowed in manual mode
        if ( command == "fwd" ) {
            motor.drive(FORWARD);
        }
        else if (command == "right") {
            motor.turn(RIGHT, turn_speed);
        }
        else if (command == "left") {
            motor.turn(LEFT, turn_speed);
        }
        else if (command == "drivestop") {
            motor.drive(IDLE);
        }
        else if (command == "noturn") {
            motor.turn(NONE, turn_speed);
        }
        else if (command == "armright") {
            motor.move_arm(CW);
        }
        else if (command == "armleft") {
            motor.move_arm(CCW);
        }
        else if (command == "armhome") {
            motor.perform_arm_macro(GO_HOME);
        }
        else if (command == "armstop") {
            motor.perform_arm_macro(STOP_ALL);
        }
        else if (command == "pickup") {
            motor.perform_arm_macro(PICK_UP);
        }
        else if (command == "putdown") {
            motor.perform_arm_macro(PUT_DOWN);
        }
        else if (command ==  "auto") {
            manual = false;

            //Important! Need to go to home position at beginning of auto mode
            motor.perform_arm_macro(GO_HOME);
        }
    }
    else{
        //Only allowed in auto mode
        if (command == "get") {
            //Retrieve new path
            if(map != nullptr && state == RobotState::STANDBY){
                //Start node of search is node behind robot
                LineNode* start_node = cur_line->get_opposite(next_node->get_id());

                cur_path = map->get_path(start_node->get_id(), stoi(parameter));

                //First driving distance will always be the same, so pop first
                cur_path.pop();

                //Go to state driving
                state = RobotState::DRIVING;
            }
        }
        else if (command == "getpos") {
            get_pos();
        }
        else if (command == "getroute") {
            get_route();
        }
        else if (command == "manual") {
            manual = true;
        }
        else if (command == "armfwd") {
            motor.move_arm(AWAY);
        }
        else if (command == "armback") {
            motor.move_arm(TOWARDS);
        }
        else if (command == "armup") {
            motor.move_arm(UP);
        }
        else if (command == "armdown") {
            motor.move_arm(DOWN);
        }
        else if (command == "closeclaw") {
            motor.control_claw(true);
        }
        else if (command == "openclaw") {
            motor.control_claw(false);
        }
    }

    //Commands allowed in both modes
    if (command == "getsensors") {
        transmit_sensors();
    }
    else if (command == "updateall") {
        transmit_sensors();
        get_pos();
        get_route();
    }
    else if (command == "estop") {
        motor.perform_arm_macro(STOP_ALL);
        motor.drive(IDLE);
        motor.turn(NONE, 0);

        state = RobotState::STANDBY;
    }
    else if (command == "calware") {
        sensor.calibrateWare();
    }
    else if (command == "calline") {
        sensor.calibrateLine();
    }
    else if (command == "calfloor") {
        sensor.calibrateFloor();
    }
    else if (command == "turnspeed") {
        turn_speed = stoi(parameter);
    }
    else if (command == "empty") {
        // TODO call set stock(parameter) as empty
    }
    else if (command == "refill") {
        // TODO call set stock(parameter) as full
    }
    else if (command == "lager") {
        delete map; //Clear memory of old map
        map = new LineMap(parameter);
    }
    else if (command == "sethome") {
        home_id = stoi(parameter);
    }
}

void Central::main_loop() {
    //Update all sensor values
    update_sensors();

    string msg_read;
    while(true) {
        //Network read
        msg_read = thread_com->read_from_queue(FROM_SOCKET);
        if (msg_read != "") {
            #ifdef DEBUG
            cout << "Msg: " << msg_read << "\n";  //prints the recieved Msg
            #endif

            handle_msg(msg_read);
        }
    }

    //Behaviour for different states in autonoumus mode
    if(!manual){
        switch(state){
            case RobotState::TURN:{
            // ~-*-~-*-~-*-~-*-~ TURN STATE ~-*-~-*-~-*-~-*-~
                switch(cur_turn_state){
                    case TurnState::NEW_TURN:{
                        //Start clock
                        clock_start = clock();

                        //Start driving forward
                        motor.drive(FORWARD);
                        cur_turn_state = TurnState::FORWARD;

                        #ifdef DEBUG
                        cout << "Driving forward" << endl;
                        #endif
                        break;
                    }
                    case TurnState::FORWARD:{
                        clock_t time_diff = clock() - clock_start;
                        if((((float)time_diff)/CLOCKS_PER_SEC) > turn_forward_time){
                            //Stop driving
                            motor.drive(IDLE);

                            //Turn different ways depending on angle
                            if(turn_angle == 2){
                                //Angle 2, continue forwars
                                #ifdef DEBUG
                                cout << "Continuing forward" << endl;
                                #endif

                                state = RobotState::DRIVING;
                            }
                            else{
                                if(turn_angle == 1){
                                    //Turn right
                                    #ifdef DEBUG
                                    cout << "Turning Right" << endl;
                                    #endif

                                    motor.turn(RIGHT, corner_turn_speed);
                                }
                                else{
                                    //Turn left
                                    #ifdef DEBUG
                                    cout << "Turning Left" << endl;
                                    #endif

                                    motor.turn(LEFT, corner_turn_speed);
                                }

                                if(line_state == SINGLE){
                                    //On opposite line
                                    cur_turn_state = TurnState::LEAVING_LINE;
                                }
                                else{
                                    cur_turn_state = TurnState::BETWEEN_LINES;
                                }
                            }
                        }
                        break;
                    }
                    case TurnState::LEAVING_LINE:{
                        if(line_state == NONE_DOUBLE){
                            //Left first line
                            cur_turn_state = TurnState::BETWEEN_LINES;
                        }
                        break;
                    }
                    case TurnState::BETWEEN_LINES:{
                        if(line_state == SINGLE){
                            //Done turning
                            #ifdef DEBUG
                            cout << "Turn Done!" << endl;
                            #endif

                            motor.turn(NONE, 0); //Stop turning

                            //Go back to driving state
                            state = RobotState::DRIVING;
                        }
                        break;
                    }
                }
                break;
            }
            case RobotState::DRIVING:{
            // ~-*-~-*-~-*-~-*-~ DRIVING STATE ~-*-~-*-~-*-~-*-~
                if(line_state == SINGLE){
                    //Follow line
                    line_follower.run(); //Run line follw system
                }
                else if(line_state == CORNER){
                    if(next_node->get_id() == home_id){
                        //At base station
                        #ifdef DEBUG
                        cout << "At home" << endl;
                        #endif

                        motor.drive(IDLE);
                        state = RobotState::DROP_OFF;
                    }
                    else{
                        //Corner found
                        state = RobotState::TURN;
                        cur_turn_state = TurnState::NEW_TURN;

                        Line* next_line = cur_path.top();

                        turn_angle = next_node->get_angle(cur_line, next_line);
                        next_node = next_line->get_opposite(next_node->get_id());
                        cur_line = next_line;

                        #ifdef DEBUG
                        cout << "Corner Found!" << endl;
                        cout << "Turning " << turn_angle << " steps." << endl;
                        #endif
                    }
                }
                else if(line_state == NONE_DOUBLE && next_node->is_leaf()){
                    //End node
                    #ifdef DEBUG
                    cout << "At target" << endl;
                    #endif

                    motor.drive(IDLE);
                    state = RobotState::PICK_UP;
                }
                break;
            }
            case RobotState::PICK_UP:{
            // ~-*-~-*-~-*-~-*-~ PICK UP STATE ~-*-~-*-~-*-~-*-~
                break;
            }
            case RobotState::DROP_OFF:{
            // ~-*-~-*-~-*-~-*-~ DROP OFF STATE ~-*-~-*-~-*-~-*-~
                break;
            }
            case RobotState::STANDBY:{
            // ~-*-~-*-~-*-~-*-~ STANDBY STATE ~-*-~-*-~-*-~-*-~
                break;
            }
            default:
            break;
        }
    }
}
