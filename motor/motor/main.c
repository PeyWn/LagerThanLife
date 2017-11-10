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
	
	while (1)
	{
		torque_enable(0xFE);
		receive_status_packet(); 
	
		move_double_axis(4, 5, 0x200, GLOBAL_SERVO_SPEED);
		
		move_single_axis(6, 0x1ff, GLOBAL_SERVO_SPEED, WRITE_DATA);
	}

}