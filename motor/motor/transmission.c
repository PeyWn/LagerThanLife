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

volatile int IS_STOP;
volatile int IS_WORKING;

volatile int cur_pos[6];
volatile int new_pos[6];
 
void transmit_startbytes()
{
	transmit(0xFF);
	transmit(0xFF); 	
}

Packet read_byte(int id, int address)
{
	transmit_startbytes();
	transmit(id);
	transmit(4);                                    // Length: Number of parameters + 2
	transmit(READ_DATA);                            // Instruction: 0x02
	transmit(address);                              // parameter 1: address to read from
    transmit(1);                                    // parameter 2: #bytes to read
	transmit( ~(id + 4 + READ_DATA + address + 1) );    //Checksum
	return receive_status_packet();
}

Packet write_byte(int id, int address, int byte, int mode)
{
    volatile char checksum = ~(id +4 +mode +address +byte);
    volatile char packet[] =  {0xFF, 0xFF, id, 4, mode, address, byte, checksum};
      
    for(int i=0; i<sizeof(packet); i++){
        transmit(packet[i]);
    }
    
    volatile int test = 1;
    
    /*
	    transmit_startbytes();
	    transmit((char)id);
	    transmit(0x04); //Number of parameters + 2 = LENGHT.
	    transmit(mode);
	    transmit(address);
	    transmit(byte);
	    transmit( ~(id + 4 + mode + address + byte) ); //Checksum
    */
    if(id != 0xFE){
	    return receive_status_packet();
    }else{
        return NO_STATUS_PACKET;
    }     
}


int read_word(int id, int address)
{
	volatile char data1 = read_byte(id, address).params[0];
	volatile char data2 = read_byte(id, address+1).params[1];
	
	return ((((short)data1)<<8) | data2); //Smash bytes together to one word. 
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
	receive_status_packet();
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
	transmit(0x02); // Length = number of parameters + 2. 
	transmit(ACTION);
	transmit(~(id+2+ACTION)); //Checksum
}

void move_double_axis(int id1, int id2, int pos, int speed) 
{
	move_single_axis(id1, pos, speed, REG_WRITE);
	_delay_ms(500);
	
	long mirror_pos = 0x03FF-pos; //Double axis's partner servo pos. 
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
	receive_status_packet();
}

void go_home_pos(void)
{
	new_pos[0] = 0x1ff;
	new_pos[1] = 0x280;
	new_pos[2] = 0x250;
	new_pos[3] = 0x0c0;
	new_pos[4] = 0x1ff;
}

void go_pos_front(void)
{
	new_pos[0] = 0x1ff;
	new_pos[1] = 0x148;
	new_pos[2] = 0x155;
	new_pos[3] = 0x100;
	new_pos[4] = 0x1ff;
}

void grab(void)
{
	new_pos[6] = 0x0f8;
}

void release(void)
{
	new_pos[6] = 0x1ff;
}

void pickup_standard_front(void)
{
	IS_WORKING = 1;
	go_pos_front();
	_delay_ms(33000); //Wait for arm to reach to object
	grab();
	go_home_pos();
	IS_WORKING = 0; 
}

void putdown_standard_front(void)
{	
	go_pos_front();
	_delay_ms(32000); //Wait for arm to reach to object 
	release();
	go_home_pos();
}

void emergency_stop(void)
{
	torque_disable_all();
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

int step_towards_pos(int axis, int new_pos[], int cur_pos[], int speed)
{
	if(!IS_STOP)
	{
		if(new_pos[axis] != cur_pos[axis])
		{
			IS_WORKING = 1;
			move_axis(axis, cur_pos[axis]+1, speed);
		}
		else
		{
			return 1;
		}
	}
	else
	{
		return 1; 
	}
	return 0; 
}