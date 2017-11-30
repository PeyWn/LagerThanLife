#include <iostream>
#include "central.h"
#include <unistd.h>
#include <time.h>
using namespace std;

Central::Central(InterThreadCom* thread_com_in) : motor(MOTOR_INTERFACE),
         sensor(SENSOR_INTERFACE),  thread_com(thread_com_in),
         line_follower(&sensor, &motor) {}

void Central::update_sensors(){
    line_center = sensor.getLineCenter();
    line_state = sensor.getLineState();
    ware_seen = sensor.getWareSeen();
}

void Central::write_sensors(){
    string to_user_interface = to_string(line_center) + " " +  to_string(line_state) +
                                " " + to_string(ware_seen.first) + " " +
                                to_string(ware_seen.second);

    thread_com->write_to_queue(to_user_interface, TO_SOCKET);

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

void Central::pick_up(){
    switch(cur_pick_up_state){	

	case(PickUpState::FIND_WARE):{
	    if(center_ware(ware_seen, &motor) == 1){
		motor.perform_arm_macro(ARM_MACRO::PICK_UP);
		cur_pick_up_state = PickUpState::PICK_UP;
	    }
	    break;}

	case(PickUpState::PICK_UP):{
	    //if(!motor.arm_active()){cur_pick_up_state = PickUpState::REVERSE;}
	    usleep(5000000);
	    t_revese = clock();
	    motor.drive(BACKWARDS, 4);
	    cur_pick_up_state = PickUpState::REVERSE;
	    break;}
	
	case(PickUpState::REVERSE):{
	    if( (float)(clock() - t_revese)/CLOCKS_PER_SEC >= PICK_REVESE_TIME ){
		motor.drive(IDLE, 0);
		motor.turn(RIGHT, 4);
		if (line_state != NONE_DOUBLE){
		    cur_pick_up_state = PickUpState::ON_LINE;
		}
		else{
		    cur_pick_up_state = PickUpState::TURN;
		}

	    }
	    break;}
	    
	case(PickUpState::ON_LINE):{
	    if(line_state == NONE_DOUBLE){
		cur_pick_up_state = PickUpState::TURN;
	    }
	    break;}
	
	case(PickUpState::TURN):{
	    if(line_state != NONE_DOUBLE){
		motor.turn(NONE, 0);
		/*    --TODO--
		      calculate route home-|
		      revese current line--|
		      change to drop_off <--
		*/
	    }
	    break;}

    }
    
}

void Central::handle_msg(string msg) {

    string command;
    string parameter;

    handle_command_parameter(msg, command, parameter);

    if ( command == "fwd" ) {
        motor.drive(FORWARD, drive_speed);
    }
    else if (command == "back") {
        motor.drive(BACKWARDS, drive_speed);
    }
    else if (command == "stop") {
        motor.drive(IDLE, 0);
    }
    else if (command == "right") {
        motor.turn(RIGHT, turn_speed);
    }
    else if (command == "left") {
        motor.turn(LEFT, turn_speed);
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
    else if (command == "get") {
        // TODO call for get(parameter) fn
    }
    else if (command == "getsensors") {
        update_sensors();
        write_sensors();
    }
    else if (command == "getpos") {
        get_pos();
    }
    else if (command == "getroute") {
        get_route();
    }
    else if (command == "updateall") {
        update_sensors();
        get_pos();
        get_route();
    }
    else if (command ==  "auto") {
        //TODO: implement
    }
    else if (command == "manual") {
        //TODO: implement
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
    else if (command == "estop") {
        motor.perform_arm_macro(STOP_ALL);
        motor.drive(IDLE, 0);
        motor.turn(NONE, 0);
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
    else if(command == "drivespeed"){
	    drive_speed = stoi(parameter);
    }
    else if (command == "empty") {
        // TODO call set stock(parameter) as empty
    }
    else if (command == "refill") {
        // TODO call set stock(parameter) as full
    }
    else if (command == "lager") {
        // TODO send parameter to abst stock to interpet lagerfile
    }
    else if (command == "sethome") {
        // TODO set parameter as home node in abst stock
    }
    else if (command == "showdata") {
        write_sensors();
    }
    else if (command == "center") {
        center_flag = 1;
    }
    else {
        // do nothing
    }

}

void Central::main_loop() {
    string msg_read;
    motor.control_claw(false);
    while(true) {
        //Network read
        msg_read = thread_com->read_from_queue(FROM_SOCKET);
        if (msg_read != "") {
            cout << "Msg: " << msg_read << "\n";  //prints the recieved Msg
            handle_msg(msg_read);
        }
	cout << "main loop: Hello" << endl;
	update_sensors();
	cout << line_state << endl;
	pick_up();

	usleep(10000);
    }
}
