/*
 * transmission.c
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

void write_byte(int id, int address, int byte, int mode)
{
	transmit_startbits();
	transmit((char)id);
	transmit(0x04); //Number of parameters + 2 = LENGHT.
	transmit(mode);
	transmit(address);
	transmit(byte);
	transmit( ~(id + 4 + mode + address + byte) );
}

void write_word(int id, int address, int word, int mode)
{
	char wordH = word >> 8;
	char wordL =  word & 0xFF;
	
	transmit_startbits();
	transmit((char)id);
	transmit(0x05); //Number of parameters + 2 = LENGHT.
	transmit(mode);
	transmit(address);
	transmit(wordL);
	transmit(wordL);
	transmit( ~(id + 4 + mode + address + wordH + wordL) );
}

void write_long(int id, int address, int word1, int word2, int mode)
{
	char word1H = word1 >> 8;
	char word1L =  word1 & 0xFF;
	
	char word2H = word2 >> 8;
	char word2L = word2 & 0xFF;
	
	transmit_startbits();
	transmit((char)id);
	transmit(0x07); //Length
	transmit(mode);
	transmit(address);
	transmit((char)word1L);
	transmit((char)word1H);
	transmit((char)word2L);
	transmit((char)word2H);
	transmit( ~(id + 7 + mode + address + word1L + word1H + word2L + word2H) );
}
 
void move_single_axis(int id, int pos, int speed, char mode) 
{
	if (mode == REG_WRITE)
	{
		write_long(id, GOAL_POSITION_ADDRESS, pos, speed, REG_WRITE);
	}
	else if (mode == WRITE_DATA)
	{
		write_long(id, GOAL_POSITION_ADDRESS, pos, speed, WRITE_DATA);
	}
}

void send_action()
{
	transmit_startbits();
	transmit(0xFE);
	transmit(0x02);
	transmit(ACTION);
	transmit(0xFA);
}

void move_double_axis(int id1, int id2, int pos, int speed) 
{
	move_single_axis(id1, pos, speed, REG_WRITE);
	
	char mirror_pos = 0x03FF-pos; 
	move_single_axis(id2, mirror_pos, speed, REG_WRITE);
	
	send_action(); 
}

void torque_enable(int id) 
{
	transmit_startbits();
	transmit((char)id);
	transmit(0x04); //Length
	transmit(WRITE_DATA);
	transmit(TORQUE_ENABLE_ADDRESS);
	transmit(1);
	transmit( ~(id + 4 + WRITE_DATA + TORQUE_ENABLE_ADDRESS + 1) );
}