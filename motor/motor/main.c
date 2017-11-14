/*
 * main.c
 *
 * Created: 11/8/2017 8:37:16 PM
 *  Author: jesjo430
 */ 

#include <avr/io.h>
#include <avr/delay.h>

#include "globals.h"
#include "init_arm.h"

#include "uart.h"
#include "uart_arm.h"

#include "transmission.h"
#include "receive.h"


int main(void)
{
	init_IO();
	usart_init(1000000);
	set_limits(); 
	
		while (1)
		{
			torque_enable(0xFE);
			
			move_single_axis(1, 0x3ff , GLOBAL_SERVO_SPEED, WRITE_DATA);
			receive_status_packet();
			
			move_single_axis(1, 0x0 , GLOBAL_SERVO_SPEED, WRITE_DATA);
			receive_status_packet();
		
			//move_double_axis(2, 3, 0x200, GLOBAL_SERVO_SPEED);
			//receive_status_packet();
		
			//move_double_axis(4, 5, 0x3FF, GLOBAL_SERVO_SPEED);
			//receive_status_packet(); 
				
			//move_single_axis(6, 0x100, GLOBAL_SERVO_SPEED, WRITE_DATA);
			//receive_status_packet();
			
			//torque_enable(0xFE);
		}
}