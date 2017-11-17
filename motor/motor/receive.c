/*
 * receive.c
 *
 * Created: 11/10/2017 9:42:17 AM
 *  Author: jesjo430
 */ 

#include <stdio.h>
#include "uart_arm.h"
#include "globals.h"

volatile int error1;
volatile int error2;
volatile int error3;
volatile int error4;
volatile int error5;
volatile int error6;
volatile int error7;
volatile int error8;

void receive_status_packet()
{
	/* Start bits 0xFF 0xFF, which is ignored */
	volatile int x = receive();
	x = receive();
	int id = receive();
	x = receive();
	int error = receive();
	
	switch(id) {
		case 1:
		error1 = error;
		break;
		
		case 2:
		error2 = error;
		break;
		
		case 3:
		error3 = error;
		break;

		case 4:
		error4 = error; 
		break;
	
		case 5:
		error5 = error; 
		break;
		
		case 6:
		error6 = error;
		break;
		
		case 7:
		error7 = id;
		break;
		
		case 8:
		error8 = error;
		break;
  
		default:
		break;
	}
}
