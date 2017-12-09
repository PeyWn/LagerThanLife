/*
 * commands.c
 *
 * Created: 11/21/2017 11:24:12 AM
 *  Author: jesjo430
 */ 

#include "transmission.h"
#include "globals.h"
#include "coordinate.h"

volatile int IS_WORKING; 
volatile int pos_cords[2]; 

/* Servo that contains position of entire axis
NOTE that axis are 0-indexed */
int AXIS_POS_SERVO[] = {1, 2, 4, 6, 7, 8};

void stop_arm(){
    for(int i = 0; i < NUMBER_OF_AXIS; ++i){
        stop_axis(i);
    }
}

void stop_axis(int id){
    //Figure out which servo to read from
    int servo_id = AXIS_POS_SERVO[id];

    //Read pos from servo
    int pos = get_servo_pos(servo_id);

    //Move axis to pos
    move_axis(id, pos, SPEED_2);
}

int get_is_working()
{
	return IS_WORKING; 
}

void grab_ware()
{
	grab();
}

void release_ware()
{
	release();
}

void go_home()
{
	//pos_cords[2] = {20, 30};
	go_home_pos(); 
}

void pick_up_ware()
{
	pickup_standard(); 
}

void put_down_ware()
{
	putdown_standard();
}

void axis_fwd(int axis){
    move_axis(axis, 0, SPEED_1);
}

void axis_back(int axis){
    move_axis(axis, 0x3ff, SPEED_1);
}


