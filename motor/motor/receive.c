/*
 * receive.c
 *
 * Created: 11/10/2017 9:42:17 AM
 *  Author: jesjo430
 */ 

#include <stdio.h>
//#include "globals.h"
#include "uart_arm.h"

volatile int x;
volatile int id4;
volatile int len4;
volatile int error4;
volatile int param4;  

void receive_status_packet()
{
	/* Start bits 0xFF 0xFF, which is ignored */
	x = receive();
	x = receive();
	id4 = receive();
	error4 = receive();
	volatile int y;
}
