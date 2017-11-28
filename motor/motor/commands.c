/*
 * commands.c
 *
 * Created: 11/21/2017 11:24:12 AM
 *  Author: jesjo430
 */ 

#include "transmission.h"
#include "globals.h"

volatile int IS_WORKING; 

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
	new_pos = CW_LIMIT_1;
}

void stop_rotate_CW()
{
	new_pos[0] = cur_pos[0];
}

void start_rotate_CCW()
{
	new_pos = CCW_LIMIT_1;
}

void stop_rotate_CCW()
{
	new_pos[0] = cur_pos[0];
}

void start_up() 
{
	for (int i = 0; i < 3; i++)
	{
		new_pos[i+1] = calculate_angels()[i];
	}
}

void stop_up()
{
	for (int i = 1; i <= 3; i++)
	{
		new_pos[i] = cur_pos[i];
	}
}

void start_down()
{
	
}

void stop_down()
{
	
}

void start_towards()
{
	
}

void stop_towards()
{
	
}

void start_away()
{
	
}

void stop_away()
{
	
}