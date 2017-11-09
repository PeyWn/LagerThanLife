/*
 * commands.c
 *
 * Created: 11/9/2017 11:38:56 AM
 *  Author: jesjo430
 */ 

#include <stdio.h>
#include <string.h>
#include "uart_arm.h"
#include "globals.h"
#include <avr/delay.h>
 
void transmit_startbits()
{
	transmit(0xFF);
	transmit(0xFF); 	
}
 
void move_singel(int id, int pos, int speed) 
{
	char posH = pos >> 8;  
	char posL =  pos & 0xFF;
	
	char speedH = speed >> 8; 
	char speedL = speed & 0xFF; 
	
	transmit_startbits();
	transmit((char)id);
	transmit(0x07); //Length
	transmit(WRITE_DATA);
	transmit(GOAL_POSITION);
	transmit((char)posL);
	transmit((char)posH);
	transmit((char)speedL);
	transmit((char)speedH);
	transmit( ~(id + 7 + WRITE_DATA + GOAL_POSITION + posL + posH + speedL +speedH) );
}

void move_double(int id, int pos, int speed) 
{
	char posH = pos >> 8;
	char posL =  pos & 0xFF;
	
	char speedH = speed >> 8;
	char speedL = speed & 0xFF;
	
	
}