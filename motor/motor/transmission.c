/*
 * transmission.c
 *
 * Created: 11/9/2017 11:38:56 AM
 *  Author: jesjo430
 */ 

#include <stdio.h>
#include <string.h>
#include <avr/delay.h>
#include "uart_arm.h"
#include "globals.h"
#include "receive.h"
 
void transmit_startbytes()
{
	transmit(0xFF);
	transmit(0xFF); 	
}

void write_byte(int id, int address, int byte, int mode)
{
	transmit_startbytes();
	transmit((char)id);
	transmit(0x04); //Number of parameters + 2 = LENGHT.
	transmit(mode);
	transmit(address);
	transmit(byte);
	transmit( ~(id + 4 + mode + address + byte) );
}

void write_word(int id, int address, int word, int mode)
{
	char wordL =  word & 0xFF;
	char wordH = word >> 8;

	transmit_startbytes();
	transmit((char)id);
	transmit(0x05); //Number of parameters + 2 = LENGHT.
	transmit(mode);
	transmit(address);
	transmit(wordL);
	transmit(wordH);
	transmit( ~(id + 4 + mode + address + wordH + wordL) );
}

void write_long(int id, int address, int word1, int word2, int mode)
{
	char word1H = word1 >> 8;
	char word1L =  word1 & 0xFF;
	
	char word2H = word2 >> 8;
	char word2L = word2 & 0xFF;
	
	transmit_startbytes();
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

void send_action(int id)
{
	transmit_startbytes();
	transmit(id);
	transmit(0x02);
	transmit(ACTION);
	transmit(~(id+2+ACTION));
}

void move_double_axis(int id1, int id2, int pos, int speed) 
{
	move_single_axis(id1, pos, speed, REG_WRITE);
	
	char mirror_pos = 0x03FF-pos; 
	move_single_axis(id2, mirror_pos, speed, REG_WRITE);
	
	send_action(id1);
	send_action(id2); 
}

void torque_enable(int id) 
{
	transmit_startbytes();
	transmit((char)id);
	transmit(0x04); //Length
	transmit(WRITE_DATA);
	transmit(TORQUE_ENABLE_ADDRESS);
	transmit(1);
	transmit( ~(id + 4 + WRITE_DATA + TORQUE_ENABLE_ADDRESS + 1) );
}

void update_error_var(int id)
{
	transmit_startbytes();
	transmit(id);
	transmit(2);
	transmit(1);
	transmit((char)~(id+2+1));
	receive_status_packet();
}