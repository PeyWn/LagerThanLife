/*
 * main.c
 *
 * Created: 11/8/2017 8:37:16 PM
 *  Author: jesjo430
 */ 

#include <avr/io.h>
#include <util/delay.h>

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
	//set_status_return_level();
	//set_return_delay_time();
	//set_limits();
	//set_torque();
	//torque_enable(0xFE);
	
		while (1)
		{
			move_single_axis(8, 0x1ff, GLOBAL_SERVO_SPEED, WRITE_DATA);
			move_single_axis(8, 0x000, GLOBAL_SERVO_SPEED, WRITE_DATA);
			move_single_axis(7, 0x000, GLOBAL_SERVO_SPEED, WRITE_DATA);
			move_single_axis(7, 0x3ff, GLOBAL_SERVO_SPEED, WRITE_DATA);
			move_single_axis(6, 0x100, GLOBAL_SERVO_SPEED, WRITE_DATA);
			move_single_axis(6, 0x200, GLOBAL_SERVO_SPEED, WRITE_DATA);
			move_double_axis(4, 5, 0x200, GLOBAL_SERVO_SPEED);
			move_double_axis(4, 5, 0x100, GLOBAL_SERVO_SPEED);
			move_double_axis(2, 3, 0x200, GLOBAL_SERVO_SPEED);
			move_double_axis(2, 3, 0x100, GLOBAL_SERVO_SPEED);
			move_single_axis(1, 0x000, GLOBAL_SERVO_SPEED, WRITE_DATA);
			move_single_axis(1, 0x3ff, GLOBAL_SERVO_SPEED, WRITE_DATA);
			
		}
}