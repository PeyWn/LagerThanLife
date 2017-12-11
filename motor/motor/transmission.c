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
#include "math.h"

volatile const double CT_ANGLE = 4.71;

void transmit_startbytes()
{
	transmit(0xFF);
	transmit(0xFF); 	
}

void send_read_msg(int id, int address, int length)
{
    // 0xff 0xff ID, LEN, INSTR,     PARAM,   PARAM, CHECKSUM
    // 0xff 0xff id,  4 , READ_DATA, address, 1,     checksum
    volatile char checksum = ~(id + 4 + READ_DATA + address + length);
    volatile char packet[] = {0xFF, 0xFF, id, 4, READ_DATA, address, length, checksum};
    
    for(int i=0; i<8; i++){
        transmit(packet[i]);
    }
}

void write_byte(int id, int address, int byte, int mode)
{
    volatile char checksum = ~(id +4 +mode +address +byte);
    volatile char packet[] =  {0xFF, 0xFF, id, 4, mode, address, byte, checksum};
      
    for(int i=0; i<sizeof(packet); i++){
        transmit(packet[i]);
    }
}

void write_word(int id, int address, int word, int mode)
{
	/* Split word into two bytes */ 
	char wordL =  word & 0xFF;
	char wordH = word >> 8;

	transmit_startbytes();
	transmit((char)id);
	transmit(0x05); //Number of parameters + 2 = LENGHT.
	transmit(mode);
	transmit(address);
	transmit(wordL);
	transmit(wordH);
	transmit( ~(id + 4 + mode + address + wordH + wordL) ); //Checksum
}

void write_long(int id, int address, int word1, int word2, int mode)
{
	/* Split words into bytes */ 
	char word1H = word1 >> 8;
	char word1L =  word1 & 0xFF;
	char word2H = word2 >> 8;
	char word2L = word2 & 0xFF;
	
	transmit_startbytes();
	transmit((char)id);
	transmit(0x07); //Length = number of parameters + 2. 
	transmit(mode);
	transmit(address);
	transmit(word1L);
	transmit(word1H);
	transmit(word2L);
	transmit(word2H);
	transmit( ~(id + 7 + mode + address + word1L + word1H + word2L + word2H) ); //Checksum
}
 
void move_single_axis(int id, int pos, int speed, char mode) 
{
	write_long(id, GOAL_POSITION_ADDRESS, pos, speed, mode);
}

void send_action(int id)
{
	transmit_startbytes();
	transmit(id);
	transmit(0x02); // Length = number of parameters + 2. 
	transmit(ACTION);
	transmit(~(id+2+ACTION)); //Checksum
}

void move_double_axis(int id1, int id2, int pos, int speed) 
{
	move_single_axis(id1, pos, speed, REG_WRITE);
	_delay_ms(500);
	
	volatile long mirror_pos = 0x03FF-pos; //Double axis's partner servo pos. 
	move_single_axis(id2, mirror_pos, speed, REG_WRITE);
	_delay_ms(500);
	
	send_action(0xFE);
}

void torque_enable(int id) 
{
	write_byte(id, TORQUE_ENABLE_ADDRESS, 1, WRITE_DATA);
}

void torque_disable_all()
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
	transmit(2); // Length = number of parameters + 2
	transmit(1);
	transmit((char)~(id+2+1)); // Checksum
}

void go_home_pos(void)
{
    move_axis(0, 0x1ff, SPEED_1);
    move_axis(1, 0x280, SPEED_1);
	_delay_ms(8000);
    move_axis(2, 0x250, SPEED_1);
    move_axis(3, 0x0c0, SPEED_1);
    move_axis(4, 0x1ff, SPEED_1);
}

void go_pos_front(void)
{
    move_axis(0, 0x1ff, SPEED_1);
    move_axis(1, 0x148, SPEED_1);
    move_axis(2, 0x155, SPEED_1);
    move_axis(3, 0x100, SPEED_1);
    move_axis(4, 0x1ff, SPEED_1);
}

void grab(void)
{
	move_axis(5, 0x0f8, SPEED_MAX);
}

void release(void)
{
    move_axis(5, 0x1ff, SPEED_MAX);
}

void pickup_standard(void)
{
	go_pos_front();
	_delay_ms(33000);
	grab();
	_delay_ms(8000);
	go_home_pos();
}

void putdown_standard(void)
{	
	go_pos_front();
	_delay_ms(33000);
	release();
	_delay_ms(8000);
	go_home_pos();
}

void move_axis(int axis, int pos, int speed)
{
	switch (axis)
	{
		case 0:
			move_single_axis(1, pos, speed, WRITE_DATA);
			break;
		case 1:
			move_double_axis(2, 3, pos, speed);
			break;
		case 2:
			move_double_axis(4, 5, pos, speed);
			break;
		case 3:
			move_single_axis(6, pos, speed, WRITE_DATA);
			break; 
		case 4: 
			move_single_axis(7, pos, speed, WRITE_DATA);
			break; 
		case 5: 
			move_single_axis(8, pos, speed, WRITE_DATA);
			break; 
	}
}

void ping_servo(int id){
    volatile char checksum = ~(id + 2 + PING);
    volatile char packet[] = {0xFF, 0xFF, id, 2, PING, checksum};
    for(int i=0; i<6; i++){
        transmit(packet[i]);
    }
}