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
#include "globals.h"

#define number_of_elem(x)  (sizeof(x) / sizeof((x)[0]))

INSTRUCTION_PACKET create_instruction_packet(int *id, int *instruction, int[] *parameters) //CHECK parameters data type
{
	INSTRUCTION_PACKET ip; 
	ip->ID = id;
	ip->INSTRUCTION = instruction;
	  
	int i = 0;
	
	for (parameters)
	  {
		ip->PARAMETERS[i] = parameters[i];
		i++; 
	  }
	  
	ip->LENGHT=number_of_elem(parameters)+2; //Length variable calculated through # of parameters + 2.  
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
