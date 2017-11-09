/*
 * main.c
 *
 * Created: 11/8/2017 8:37:16 PM
 *  Author: jesjo430
 */ 

#include <avr/io.h>
#include "uart.h"
#include "init_arm.h"
#include "uart_arm.h"
#include "globals.h"
#include <avr/delay.h>
#include "commands.h"


int main(void)
{
	init_IO();
	usart_init(1000000);
    
	while (1)
	{
		//move_double(2, 3, 0x200, GLOBAL_SERVO_SPEED);
		move_double(4, 5, 0x200, GLOBAL_SERVO_SPEED);
		//move_singel(18, 0x200, GLOBAL_SERVO_SPEED, WRITE_DATA);
	}

}