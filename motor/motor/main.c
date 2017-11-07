/*
 * motor.c
 *
 * Created: 11/1/2017 8:55:44 AM
 *  Author: jakno732
 */ 


#include <avr/io.h>
#include "uart.h"
#include "init_arm.h"

int main(void)
{
	init_IO();
	usart_init();
	PORTD |= (1<<PORTD4);
	
	
		usart_transmit(0xFF);
		usart_transmit(0xFF);
		usart_transmit(0xFE); //ID = FE.
		usart_transmit(0x04); //LENGTH = 4.
		usart_transmit(0x03); //Instruction = write.
		usart_transmit(0x19); //Parameter 1 --> Control table address = 0x19 => LED.
		usart_transmit(0x01); //Parameter 2 --> data = 1 to be written. 
		usart_transmit(0xE0); //CHECKSUM
	
	
	while(1)
    {
	//	usart_transmit(0b10000010);
    }
}