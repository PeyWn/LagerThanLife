/*
 * receive.c
 *
 * Created: 11/10/2017 9:42:17 AM
 *  Author: jesjo430
 */ 

#include <stdio.h>
#include "uart_arm.h"
#include "globals.h"

int error1;
int error2;
int error3;
int error4;
int error5;
int error6;
int error7;
int error8;

void receive_status_packet()
{
	/* Start bits 0xFF 0xFF, which is ignored */
	int x = receive();
	x = receive();
	int id = receive();
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
