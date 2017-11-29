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

const double CT_ANGLE = 4.71; 

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

void stop_all()
{
	emergency_stop(); 
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

void start_rotate_CW()
{
	new_pos[0] = CW_LIMIT_1;
}

void stop_rotate_CW()
{
	new_pos[0] = cur_pos[0];
}

void start_rotate_CCW()
{
	new_pos[0] = CCW_LIMIT_1;
}

void stop_rotate_CCW()
{
	new_pos[0] = cur_pos[0];
}

void start_up() 
{
	step_new_pos('u'); 
}

void stop_up()
{
	stop_all(); 
}

void start_down()
{
	
}

void stop_down()
{
	stop_all(); 
}

void start_towards()
{
	
}

void stop_towards()
{
	stop_all(); 
}

void start_away()
{
	
}

void stop_away()
{
	stop_all(); 
}