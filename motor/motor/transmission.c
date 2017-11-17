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

volatile int is_working; 
 
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

char read_byte(int id, int address)
{
	transmit_startbytes();
	transmit(id);
	transmit(0x03); //Number of parameters + 2 = LENGHT.
	transmit(READ_DATA);
	transmit(address);
	transmit( ~(id + 3 + READ_DATA + address) );
	return receive_status_packet();
}

int read_word(int id, int address)
{
	volatile char data1 = read_byte(id, address);
	volatile char data2 = read_byte(id, address+1);
	
	return ((((short)data1)<<8) | data2); 
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

void torque_disable(int id)
{
	for (int i = 1; i<=NUMBER_OF_MOTORS; i++)
	{
		write_byte(i, TORQUE_ENABLE_ADDRESS, 0, WRITE_DATA);
	}
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
	move_double_axis(4, 5, 0x250, SPEED_3);
	_delay_ms(8000);
	move_single_axis(6, 0xC0, SPEED_2, WRITE_DATA);
	move_single_axis(7, 0x1ff, SPEED_2, WRITE_DATA);
}

void go_pos_front(void)
{
	move_single_axis(1, 0x1ff, SPEED_2, WRITE_DATA);
	move_double_axis(4, 5, 0x155, SPEED_3);
	move_single_axis(6, 0x100, SPEED_2, WRITE_DATA);
	move_single_axis(7, 0x1ff, SPEED_2, WRITE_DATA);
	move_double_axis(2, 3, 0x148, SPEED_4);
}

void grab(void)
{
	move_single_axis(8, 0xf8, SPEED_MAX, WRITE_DATA);
}

void release(void)
{
	move_single_axis(8, 0x1ff, SPEED_MAX, WRITE_DATA);
}

void pickup_standard_front(void)
{
	is_working = 1;
	go_pos_front();
	_delay_ms(33000);
	grab();
	go_home_pos();
	is_working = 0; 
}

void putdown_standard_front(void)
{
	is_working = 1; 
	go_pos_front();
	_delay_ms(32000);
	release();
	go_home_pos();
	is_working = 0;
}

void emergency_stop(void)
{
	torque_disable(0xFE);
}