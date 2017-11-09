/*
 * main.c
 *
 * Created: 11/8/2017 8:37:16 PM
 *  Author: jesjo430
 */ 

#include <avr/io.h>
#include "uart.h"
#include "init_arm.h"
#include "uart_arm.h"


/* turn on led */
void test_turn_on_LED(char id){
    transmit(0xFF);
    transmit(0xFF);
    transmit(id); //ID = FE.
    transmit(0x04); //LENGTH = 4.
    transmit(0x03); //Instruction = write.
    transmit(0x19); //Parameter 1 --> Control table address = 0x19 => LED.
    transmit(0x01); //Parameter 2 --> data = 1 to be written. TURN ON
    transmit( ~(id + 0x04 + 0x03 + 0x19 + 0x01) ); //CHECKSUM
}

/* turn off led */
void test_turn_off_LED(char id){
    transmit(0xFF);
    transmit(0xFF);
    transmit(id); //ID - 18 is motor, 0xFE is broadcast
    transmit(0x04); //LENGTH = 4.
    transmit(0x03); //Instruction = write.
    transmit(0x19); //Parameter 1 --> Control table address = 0x19 => LED.
    transmit(0x00); //Parameter 2 --> data = 0 to be written. TURN OFF
    transmit( ~(id + 0x04 + 0x03 + 0x19 + 0x00) ); //CHECKSUM
}

/* read ID - "return ID!" */
void test_read_ID(char id){
    transmit(0xFF);
    transmit(0xFF);
    transmit(id);   // ID = 18.
    transmit(0x04); // LENGTH = 4.
    transmit(0x02); // Instruction: read
    transmit(0x03); // Parameter 1: address to read at
    transmit(0x01); // Parameter 2: bytes of data to read
    transmit( ~(id + 0x04 + 0x02 + 0x03 + 0x01) ); // checksum

}

/* receive ID from status packet (broadcast receives no status packets) */
char test_receive_ID(){
    volatile char id = 0; 
	volatile char x  = 0;
	x = receive();                // 0xFF
    x = receive();                // 0xFF
    id = receive();       // 18   - ID, not read from address)
    x = receive();                // 0x03 - length
    x = receive();                // 0x00 - error
    x = receive();                // checksum
    return id;
}

/* transmit PING instruction */
void test_ping(char id){
    transmit(0xFF);
    transmit(0xFF);
    transmit(id);   // ID = 18.
    transmit(0x02); // LENGTH = 4.
    transmit(0x01); // Instruction: Ping (get status packet)
    transmit( ~(id + 0x02 + 0x01) ); // checksum
}

/* set return delay time */
void test_set_return_delay_time(char id, char delay){
    transmit(0xFF);
    transmit(0xFF);
    transmit(id); //ID - 18 is motor, 0xFE is broadcast
    transmit(0x04); //LENGTH = 4.
    transmit(0x03); //Instruction = write.
    transmit(0x05); //Parameter 1 --> Control table address = 0x19 => LED.
    transmit(delay); //Parameter 2 --> data = 0 to be written. TURN OFF
    transmit( ~(id + 0x04 + 0x03 + 0x19 + delay) ); //CHECKSUM
}

int main(void)
{
	init_IO();
	usart_init(1000000);
    
	
    /* test if data is received*/
	test_turn_on_LED(18);
	char id = test_receive_ID();
	if (id == 18){
		test_turn_off_LED(18);
	}
	    
	while (1)
	{
		
	}

}