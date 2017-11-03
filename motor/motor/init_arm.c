/*
 * init_arm.c
 *
 * Created: 11/3/2017 11:54:22 AM
 *  Author: jesjo430
 */ 

void init_IO(void)
{
	PORTD2 = 0; //Set D02 to be input. Rx for UART communication with arm.  
	PORTD3 = 1; //Set D03 to be output. Tx for UART communication with arm. 
	PORTD4 = 1; //Set D04 to be output. Used as direction chooser for duplex-UART.  
}
