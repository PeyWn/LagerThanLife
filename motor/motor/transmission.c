/*
 * transmission.c
 *
 * Created: 11/9/2017 11:38:56 AM
 *  Author: jesjo430
 */ 

#include <stdio.h>
#include <string.h>
#include <util/delay.h>
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
	receive_status_packet();
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
	receive_status_packet();
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
	transmit(word1L);
	transmit(word1H);
	transmit(word2L);
	transmit(word2H);
	transmit( ~(id + 7 + mode + address + word1L + word1H + word2L + word2H) );
	receive_status_packet();
}
 
void move_single_axis(int id, int pos, int speed, char mode) 
{
	write_long(id, GOAL_POSITION_ADDRESS, pos, speed, mode);
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
	_delay_ms(500);
	
	long mirror_pos = 0x03FF-pos; 
	move_single_axis(id2, mirror_pos, speed, REG_WRITE);
	_delay_ms(500);
	
	send_action(0xFE);
}

void torque_enable(int id) 
{
	write_byte(id, TORQUE_ENABLE_ADDRESS, 1, WRITE_DATA);
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

void go_home_pos(void)
{
	move_double_axis(2, 3, 0x280, SPEED_4);
	move_single_axis(1, 0x1ff, SPEED_2, WRITE_DATA);
	move_double_axis(4, 5, 0x250, SPEED_2);
	move_single_axis(6, 0xC0, SPEED_2, WRITE_DATA);
	move_single_axis(7, 0x1ff, SPEED_2, WRITE_DATA);
}

void go_pos_front(void)
{
	move_single_axis(1, 0x1ff, SPEED_2, WRITE_DATA);
	move_double_axis(4, 5, 0x160, SPEED_3);
	move_single_axis(6, 0x100, SPEED_2, WRITE_DATA);
	move_single_axis(7, 0x1ff, SPEED_2, WRITE_DATA);
	move_double_axis(2, 3, 0x148, SPEED_2);
}

void grab(void)
{
	move_single_axis(8, 0xf8, SPEED_4, WRITE_DATA);
}

void release(void)
{
	move_single_axis(8, 0x1ff, SPEED_4, WRITE_DATA);
}

void go_pickup_standard(void)
{
	go_pos_front();
	grab();
}

void go_release_front(void)
{
	go_pos_front();
	release();
}

void pickup_standard_front(void)
{
	go_pos_front();
	_delay_ms(50000);
	grab();
	_delay_ms(21000);
	go_home_pos();
}

void putdown_standard_front(void)
{
	go_pos_front();
	_delay_ms(50000);
	release();
	_delay_ms(21000);
	go_home_pos();
}