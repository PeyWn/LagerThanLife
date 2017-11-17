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
