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
			update_error_var(2);
			
			//torque_enable(0xFE);
			//set_torque();
			
			//move_single_axis(1, 0x1ff , GLOBAL_SERVO_SPEED, WRITE_DATA);
			
			//move_single_axis(6, 0x200, GLOBAL_SERVO_SPEED, WRITE_DATA);
			
			//move_double_axis(2, 3, 0x1FF, GLOBAL_SERVO_SPEED);
			
			//move_double_axis(4, 5, 0x1FF, GLOBAL_SERVO_SPEED);
		}
}