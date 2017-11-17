<<<<<<< HEAD
﻿/*
 * main.c
 *
 * Created: 11/8/2017 8:37:16 PM
 *  Author: jesjo430
 */

#include <avr/io.h>
#include <util/delay.h>

#include "globals.h"
#include "init_arm.h"

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
			//release();
			pickup_standard_front();
			putdown_standard_front();
		}
}
=======
#include <avr/io.h>
#include <avr/interrupt.h>
#include "wheel_control.h"

int main(void)
{
    /*
    init_wheel_control(0.3);    
    update_wheel_control();     // test routine 
    */
	
	//Conf UART
	
	//set rx to input, set tx to output
	DDRD = (0<<DDD0)|(1<<DDD1);	
	
	UBRR0L = 0x67; //BAUDRATE 103
	
	//Set UART baudrate, activates Tx/Rx, activates interrupts for UART data recieved
	UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);
	
	//Enable global interrupts
	sei();
	

    while(1)
    {
		
    }
    return 0;
}
>>>>>>> origin/master
