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


int main(void)
{
	init_IO();
	usart_init(1000000);
    
	while (1)
	{
		move_double_axis(4, 5, 0x200, GLOBAL_SERVO_SPEED);
		torque_enable(0xFE);
	}

}