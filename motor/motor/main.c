/*
 * motor.c
 *
 * Created: 11/1/2017 8:55:44 AM
 *  Author: jakno732
 */ 


#include <avr/io.h>
#include "uart.h"
#include "init_arm.h"
#include "uart_arm.h"


/* turn on led */
void test_turn_on_LED(){
    transmit(0xFF);
    transmit(0xFF);
    transmit(0xFE); //ID = FE.
    transmit(0x04); //LENGTH = 4.
    transmit(0x03); //Instruction = write.
    transmit(0x19); //Parameter 1 --> Control table address = 0x19 => LED.
    transmit(0x01); //Parameter 2 --> data = 1 to be written. TURN ON
    transmit( ~(18 + 0x04 + 0x03 + 0x19 + 0x01) ); //CHECKSUM
    //transmit(0x00);
}

/* turn off led */
void test_turn_off_LED(){
    transmit(0xFF);
    transmit(0xFF);
    transmit(18); //ID - 18 is motor, 0xFE is broadcast
    transmit(0x04); //LENGTH = 4.
    transmit(0x03); //Instruction = write.
    transmit(0x19); //Parameter 1 --> Control table address = 0x19 => LED.
    transmit(0x00); //Parameter 2 --> data = 0 to be written. TURN OFF
    transmit( ~(18 + 0x04 + 0x03 + 0x19 + 0x00) ); //CHECKSUM
}

/* read ID - "return ID!" */
void test_read_ID(){
    transmit(0xFF);
    transmit(0xFF);
    transmit(18);   // ID = 18.
    transmit(0x04); // LENGTH = 4.
    transmit(0x02); // Instruction: read
    transmit(0x03); // Parameter 1: address to read at
    transmit(0x01); // Parameter 2: bytes of data to read
    transmit( ~(18 + 0x04 + 0x02 + 0x03 + 0x01) ); // checksum

}


/* receive ID from status packet (broadcast receives no status packets) */
char test_receive_ID(){
    receive();                // 0xFF
    receive();                // 0xFF
    char id =receive();                // 18   - ID, not read from address)
    receive();                // 0x03 - length
    receive();                // 0x00 - error
    receive();                // checksum
    return id;
}

/* transmit PING instruction */
void test_ping(){
    transmit(0xFF);
    transmit(0xFF);
    transmit(18);   // ID = 18.
    transmit(0x02); // LENGTH = 4.
    transmit(0x01); // Instruction: Ping (get status packet)
    transmit( ~(18 + 0x02 + 0x01) ); // checksum
}

int main(void)
{
	init_IO();
	usart_init(1000000);
    
    /* test if data is received*/
    while(1){
		test_turn_off_LED();
		for (int i = 0; i<11512; i++);
		test_turn_on_LED();
		for (int i = 0; i<11512; i++);
    }    

}