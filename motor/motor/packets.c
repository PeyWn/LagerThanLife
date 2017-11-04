/*
 * packets.c
 *
 * Created: 2017-11-04 18:08:47
 *  Author: Jesper
 */ 

#include <stdio.h>
#include <avr/io.h>
#include <stdlib.h>
#include "packets.h"

typedef struct
{
	static int STARTBIT_0 = 0xFF,
			   STARTBIT_1 = 0xFF;
		   int ID,
			   LENGHT,
			   INSTRUCTION,
			   PARAMETER_1, //CHECK
			   //...
			   PARAMETER_N,
			   CHECK_SUM;
}INSTRUCTION_PACKET;

typedef struct
{
	static int STARTBIT_0 = 0xFF,
			   STARTBIT_1 = 0xFF;
		   int ID,
			   LENGHT,
			   ERROR,
			   PARAMETER_1, //CHECK
			   //...
			   PARAMETER_N,
			   CHECK_SUM;
}STATUS_PACKET;