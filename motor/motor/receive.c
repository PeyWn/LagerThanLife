/*
 * receive.c
 *
 * Created: 11/10/2017 9:42:17 AM
 *  Author: jesjo430
 */ 

#include <stdio.h>
#include "globals.h"
#include "uart_arm.h"

int id4;
int len4;
int error4;
int param4;

void receive_status_packet()
{
	/* Start bits 0xFF 0xFF, which is ignored */
	receive();
	receive();
	volatile id4 = receive();
	len4 = receive();
	error4 = receive();
	param4 = receive();
	
	for (int i = 1; i < len4; i++)
	{
		receive();
	}
	receive();
}

