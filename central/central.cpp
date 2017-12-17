#include "central.h"
#include <time.h>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <stdexcept>

using namespace std;

Central::Central(InterThreadCom* thread_com_in) : motor(MOTOR_INTERFACE),
         sensor(SENSOR_INTERFACE),  thread_com(thread_com_in),
         line_follower(&motor) {}

void Central::transmit_sensors(){
    string to_user_interface = to_string(line_center) +
                                " " +  to_string(line_state) +
                                " " + to_string(ware_seen.first) + " " +
                                to_string(ware_seen.second);

    thread_com->write_to_queue(to_user_interface, TO_SOCKET);
}

void Central::update_sensors(){
      /* Update state before center to avoid issues when sensor
      updates happens between calls. */
      line_state = sensor.get_line_state();
      line_center = sensor.get_line_center();

	    ware_seen = sensor.get_ware_seen();
}

void Central::get_pos(){
    string send_string;

    if(cur_line == nullptr || next_node == nullptr){
        //If autonoumus mode started return just 0 0
        send_string = "0 0";
    }
    else{
        int to_id = next_node->get_id();
        int from_id = cur_line->get_opposite(to_id)->get_id();

        send_string = to_string(from_id) + " " + to_string(to_id);
    }

    thread_com->write_to_queue(send_string, TO_SOCKET);
}


void Central::get_route(){
    vector<int> node_order;

    if(cur_path.size() == 0){
        //Empty path, not on a route
        node_order.push_back(0);
    }
    else{
        //Copy path to not break navigation
        stack<Line*> path_copy = cur_path;
        LineNode* node_iter = next_node;

        node_order.push_back(node_iter->get_id());

        while(!path_copy.empty()){
            node_iter = path_copy.top()->get_opposite(node_iter->get_id());

            path_copy.pop();
            node_order.push_back(node_iter->get_id());
        }
    }

    string return_msg;
    for(int id : node_order){
        return_msg += to_string(id) + " ";
    }

    thread_com->write_to_queue(return_msg, TO_SOCKET);
}

void Central::handle_command_parameter(string msg_with_parameter,
    string& command, string& parameter){

    string delimiter = " ";
    size_t pos = 0;

    pos = msg_with_parameter.substr(0,
            msg_with_parameter.find_first_of(" ")).length();

    if (pos > 0){
        command = msg_with_parameter.substr(0, pos);
        msg_with_parameter.erase(0, pos + delimiter.length());
        parameter = msg_with_parameter;
    }
    else {
        command = msg_with_parameter;
    }
}

void Central::pick_up(){
    switch(cur_pick_up_state){
        case(PickUpState::FIND_WARE):{
            if(center_ware(ware_seen, &motor) == 1){
                motor.control_claw(false);
        		    motor.perform_arm_macro(ARM_MACRO::PICK_UP);
			    clock_set = clock();
			    cur_pick_up_state = PickUpState::PICK_UP;

            }
            break;}

        case(PickUpState::PICK_UP):{
            #ifdef DEBUG
            cout << "Pick up state: PICK_UP" << endl;
            #endif
	    clock_diff = clock() - clock_set;
            if( ( delay_time  < ((float)clock_diff)/CLOCKS_PER_SEC) ){
		cur_pick_up_state = PickUpState::START_TURN;
	    }
            break;
        }
        case(PickUpState::START_TURN):{
            #ifdef DEBUG
            cout << "Pick up state: START_TURN" << endl;
            #endif

            motor.turn(RIGHT, CORNER_TURN_SPEED);
            if (line_state != NONE_DOUBLE){
        	    cur_pick_up_state = PickUpState::ON_LINE;
            }
            else{
                cur_pick_up_state = PickUpState::TURN;
            }

            break;}

        case(PickUpState::ON_LINE):{
        	#ifdef DEBUG
          cout << "Pick up state: ON_LINE" << endl;
          #endif
          if(line_state == NONE_DOUBLE){
        	    cur_pick_up_state = PickUpState::TURN;
          }
          break;}

        case(PickUpState::TURN):{
            #ifdef DEBUG
            cout << "Pick up state: TURN" << endl;
                #endif
            if( (line_state != NONE_DOUBLE) && (abs(line_center) < CORNER_LINE_THRESHOLD) ){
        	motor.turn(NONE, 0);

        	next_node = cur_line->get_opposite(next_node->get_id());
        	cur_path = map->get_path(next_node->get_id(), home_id);

        	cur_pick_up_state = PickUpState::FIND_WARE;
        	motor.drive(FORWARD, AUTO_DRIVE_SPEED);
        	state = RobotState::DRIVING;
            }
            break;}

    }
}


void Central::drop_off(){
    switch(cur_drop_off_state){
	case(DropOffState::START):{
	    clock_set = clock();
	    cur_drop_off_state = DropOffState::PUT_DOWN;
	    break;}


	case(DropOffState::PUT_DOWN):{
            #ifdef DEBUG
            cout << "Drop off: put down" << endl;
            #endif

            motor.perform_arm_macro(ARM_MACRO::PUT_DOWN);

	    clock_diff = clock() - clock_set;
            if( ( delay_time  < ((float)clock_diff)/CLOCKS_PER_SEC) ){
		motor.turn(RIGHT, CORNER_TURN_SPEED);
		cur_drop_off_state = DropOffState::TURN_CORNER;
	    }

	    break;}

        case(DropOffState::TURN_CORNER):{
            #ifdef DEBUG
            cout << "Drop off: corner" << endl;
            #endif

            if(line_state == NONE_DOUBLE){
                cur_drop_off_state = DropOffState::TURN_NONE;
            }
            break;}

        case(DropOffState::TURN_NONE):{
            #ifdef DEBUG
            cout << "Drop off: none" << endl;
            #endif

            if( (line_state == SINGLE) && (abs(line_center) < CORNER_LINE_THRESHOLD) ){
                motor.turn(NONE, 0);
              	cur_drop_off_state = DropOffState::START;
              	state = RobotState::STANDBY;
            }
            break;}
    }
}

void Central::handle_msg(string msg) {

    string command;
    string parameter;

    handle_command_parameter(msg, command, parameter);

    if(manual){
        //Only allowed in manual mode
        if ( command == "fwd" ) {
            motor.drive(FORWARD, drive_speed);

            #ifdef DEBUG
            cout << "Driving forward." << endl;
            #endif
        }
        else if (command == "back") {
            motor.drive(BACKWARDS, drive_speed);

            #ifdef DEBUG
            cout << "Driving backwards." << endl;
            #endif
        }
        else if (command == "stop") {
            motor.drive(IDLE, 0);
        }
        else if (command == "right") {
            motor.turn(RIGHT, turn_speed);

            #ifdef DEBUG
            cout << "Turning right." << endl;
            #endif
        }
        else if (command == "left") {
            motor.turn(LEFT, turn_speed);

            #ifdef DEBUG
            cout << "Turning left." << endl;
            #endif
        }
        else if (command == "noturn") {
            motor.turn(NONE, turn_speed);
        }
        else if (command == "armright") {
            motor.move_arm(0, true);
        }
        else if (command == "armleft") {
            motor.move_arm(0, false);
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
        else if (command == "arm1fwd") {
            motor.move_arm(1, true);
        }
        else if (command == "arm1back") {
            motor.move_arm(1, false);
        }
        else if (command == "arm2fwd") {
            motor.move_arm(2, true);
        }
        else if (command == "arm2back") {
            motor.move_arm(2, false);
        }
        else if (command == "arm3fwd") {
            motor.move_arm(3, true);
        }
        else if (command == "arm3back") {
            motor.move_arm(3, false);
        }
        else if (command == "closeclaw") {
            motor.control_claw(true);
        }
        else if (command == "openclaw") {
            motor.control_claw(false);
        }
        else if (command ==  "auto") {
            manual = false;

            #ifdef DEBUG
            cout << "Switched to auto mode." << endl;
            #endif

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

                cur_path = map->get_path(home_id, stoi(parameter));

        		cur_line = cur_path.top();
        		next_node = cur_line->get_opposite(home_id);

                //First driving distance will always be the same, so pop first
                cur_path.pop();

        		#ifdef DEBUG
        		cout << "Going to pos " << parameter  << endl;
        		#endif

                //Go to state driving
                state = RobotState::DRIVING;
                motor.drive(FORWARD, AUTO_DRIVE_SPEED);
            }
        }
        else if (command == "manual") {
            manual = true;

    	    #ifdef DEBUG
    	    cout << "Switched to manual mode." << endl;
    	    #endif
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
        motor.drive(IDLE, 0);
        motor.turn(NONE, 0);

        state = RobotState::STANDBY;
    }
    else if (command == "calware") {
        sensor.calibrate_ware();

        #ifdef DEBUG
        cout << "Ware sensors calibrated." << endl;
        #endif
    }
    else if (command == "calline") {
        sensor.calibrate_line();

        #ifdef DEBUG
        cout << "Line sensor calibrated for line." << endl;
        #endif
    }
    else if (command == "calfloor") {
        sensor.calibrate_floor();

        #ifdef DEBUG
        cout << "Line sensor calibrated for floor." << endl;
        #endif
    }
    else if (command == "turnspeed") {
        turn_speed = stoi(parameter);
    }
    else if(command == "drivespeed"){
        drive_speed = stoi(parameter);
    }
    else if (command == "lager") {
        delete map;
        map = new LineMap(parameter);

        #ifdef DEBUG
        cout << "LineMap of size " << map->get_node_c() << " loaded." << endl;
        #endif
    }
    else if (command == "sethome") {
        home_id = stoi(parameter);

        #ifdef DEBUG
        cout << "Home set to node " << home_id << "." << endl;
        #endif
    }
    else if (command == "getpos") {
        get_pos();
    }
    else if (command == "getroute") {
        get_route();
    }
}

void Central::main_loop() {
    string msg_read;
    //Move arm to home position when starting
    motor.perform_arm_macro(GO_HOME);

    while(true) {
        //Start the main loop clock
        main_loop_clock = clock();

        //Update all sensor values
        update_sensors();

        //Network read
        msg_read = thread_com->read_from_queue(FROM_SOCKET);

        if (msg_read != "") {
            #ifdef DEBUG
            cout << "Msg: " << msg_read << "\n";  //prints the recieved Msg
            #endif

            handle_msg(msg_read);
        }

        if(!manual){
            switch(state){
                case RobotState::TURN:{
                    turn_state();
                    break;
                }
                case RobotState::DRIVING:{
                    drive_state();
                    break;
                }
                case RobotState::PICK_UP:{
                    pick_up();
                    break;
                }
                case RobotState::DROP_OFF:{
		                drop_off();
                    break;
                }
                case RobotState::STANDBY:{
                    break;
                }
                default:
                break;
            }
        }

    	  //Delay main loop slightly to not spam UART
        //Delay is calculated based on time left to keep delay constant
        double elapsed_sec = (float)(clock() - main_loop_clock)/CLOCKS_PER_SEC;

        double sleep_time = (MAIN_LOOP_DELAY - elapsed_sec) * 1000000;
        usleep(sleep_time);
    }
}

void Central::turn_state(){
    switch(cur_turn_state){
        case TurnState::NEW_TURN:{
            clock_start = clock();
            motor.drive(FORWARD, AUTO_DRIVE_SPEED);
            cur_turn_state = TurnState::FORWARD;

            #ifdef DEBUG
            cout << "Driving forward" << endl;
            #endif
            break;
        }
        case TurnState::FORWARD:{
            clock_t time_diff = clock() - clock_start;
            if((((float)time_diff)/CLOCKS_PER_SEC) > TURN_FORWARD_TIME){
                if(turn_angle == 2){
                    #ifdef DEBUG
                    cout << "Continuing forward" << endl;
                    #endif

                    state = RobotState::DRIVING;
                }
                else{
                    //Stop driving
		            motor.drive(IDLE, 0);

                    if(turn_angle == 1){
                        #ifdef DEBUG
                        cout << "Turning Right" << endl;
                        #endif

                        motor.turn(RIGHT, CORNER_TURN_SPEED);
                    }
                    else{
                        #ifdef DEBUG
                        cout << "Turning Left" << endl;
                        #endif

                        motor.turn(LEFT, CORNER_TURN_SPEED);
                    }

                    if(line_state == SINGLE){
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
                cur_turn_state = TurnState::BETWEEN_LINES;
            }
            break;
        }
        case TurnState::BETWEEN_LINES:{
            if(line_state == SINGLE &&
                (abs(line_center) < CORNER_LINE_THRESHOLD)){
                #ifdef DEBUG
                cout << "Turn Done!" << endl;
                #endif

                motor.turn(NONE, 0);
                motor.drive(FORWARD, AUTO_DRIVE_SPEED);
                state = RobotState::DRIVING;
            }
            break;
        }
    }
}

void Central::drive_state(){
    if(line_state == SINGLE){
        line_follower.run(line_center); //Run line follower system
    }
    else if(line_state == CORNER){
        if(next_node->get_id() == home_id){
            #ifdef DEBUG
            cout << "At home" << endl;
            #endif

            motor.turn(NONE, 0);
	          motor.drive(IDLE, 0);
            cur_drop_off_state = DropOffState::PUT_DOWN;
            state = RobotState::DROP_OFF;
        }
        else{
    	    if(cur_path.empty()){
    		    throw invalid_argument("Corner found when current path is empty");
    	    }

    	    #ifdef DEBUG
    	    cout << "Corner Found!" << endl;
    	    #endif

            state = RobotState::TURN;
            cur_turn_state = TurnState::NEW_TURN;

            Line* next_line = cur_path.top();
            cur_path.pop();

            turn_angle = next_node->get_angle(cur_line, next_line);
            next_node = next_line->get_opposite(next_node->get_id());
            cur_line = next_line;

            #ifdef DEBUG
            cout << "Turning " << turn_angle << " steps." << endl;
            cout << "Next node will be " << next_node->get_id() << endl;
            #endif
        }
    }
    else if(line_state == NONE_DOUBLE && next_node->is_leaf() && next_node->get_id() != home_id){
        #ifdef DEBUG
        cout << "At target" << endl;
        #endif

        motor.drive(IDLE, 0);
        motor.turn(NONE, 0);
        cur_pick_up_state = PickUpState::FIND_WARE;
        state = RobotState::PICK_UP;
    }
}
