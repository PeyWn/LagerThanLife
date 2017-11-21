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
	pickup_standard_front(); 
}

void put_down_ware()
{
	putdown_standard_front();
}

void start_rotate_CW()
{
	
}

void stop_rotate_CW()
{
	
}

void start_rotate_CCW()
{
	
}

void stop_rotate_CCW()
{
		
}

void start_up() 
{
	
}

void stop_up()
{
	
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