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

INSTRUCTION_PACKET create_instruction_packet(int *id, int *instruction, int[] *parameters) //CHECK parameters data type
{
  INSTRUCTION_PACKET *ip = (INSTRUCTION_PACKET*)malloc(sizeof(INSTRUCTION_PACKET)); //Maybe not malloc. Ckeck sensor/globals.h + main.c
	  ip->ID = id;
	  ip->INSTRUCTION = instruction;
	  
	  int lenght_counter = 0;

	  for ()
	  {
		  //build parameters.
	  }
	  
	  //calculate checksum and length then assign them to struct. 
}

INSTRUCTION_PACKET set_ip_id(INSTRUCTION_PACKET *ip, int *id)
{
	ip->ID = id; //Check pointers handling
	return ip;   // same. 
}

INSTRUCTION_PACKET set_ip_instruction(INSTRUCTION_PACKET *ip, int *instruction)
{
	ip->INSTRUCTION = instruction; //Check pointers handling
	return ip;   // same.
}	

INSTRUCTION_PACKET set_ip_parameters(INSTRUCTION_PACKET *ip, int[] *parameters)
{
	//DO. 
}
