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
<<<<<<< HEAD
    transmit(8); //ID = FE.
=======
    transmit(0xFE); //ID = FE.
>>>>>>> parent of 6fd476a... Show anders Commit
    transmit(0x04); //LENGTH = 4.
    transmit(0x03); //Instruction = write.
    transmit(0x19); //Parameter 1 --> Control table address = 0x19 => LED.
    transmit(0x01); //Parameter 2 --> data = 1 to be written. TURN ON
<<<<<<< HEAD
    transmit( ~(8 + 0x04 + 0x03 + 0x19 + 0x01) ); //CHECKSUM
=======
    transmit( ~(18 + 0x04 + 0x03 + 0x19 + 0x01) ); //CHECKSUM
    //transmit(0x00);
>>>>>>> parent of 6fd476a... Show anders Commit
}

/* turn off led */
void test_turn_off_LED(){
    transmit(0xFF);
    transmit(0xFF);
    transmit(0xFE); //ID - 18 is motor, 0xFE is broadcast
    transmit(0x04); //LENGTH = 4.
    transmit(0x03); //Instruction = write.
    transmit(0x19); //Parameter 1 --> Control table address = 0x19 => LED.
    transmit(0x00); //Parameter 2 --> data = 0 to be written. TURN OFF
    transmit( ~(0xFE + 0x04 + 0x03 + 0x19 + 0x00) ); //CHECKSUM
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
<<<<<<< HEAD
	char id = 0;
    id += receive();                // 0xFF
    id += receive();                // 0xFF
    id += receive();       // 18   - ID, not read from address)
    id += receive();                // 0x03 - length
    id += receive();                // 0x00 - error
    id += receive();                // checksum
=======
    receive();                // 0xFF
    receive();                // 0xFF
    char id =receive();                // 18   - ID, not read from address)
    receive();                // 0x03 - length
    receive();                // 0x00 - error
    receive();                // checksum
>>>>>>> parent of 6fd476a... Show anders Commit
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

void test_turn(){
    transmit(0xFF);
    transmit(0xFF);
    transmit(18); //ID - 18 is motor, 0xFE is broadcast
    transmit(0x07); //LENGTH = 4.
    transmit(0x03); //Instruction = write.
    transmit(0x1E); //Parameter 1 --> Control table address = 0x19 => LED.
    transmit(0x00); //Parameter 2 --> data = 0 to be written. TURN OFF
	transmit(0x02);
	transmit(0x00);
	transmit(0x02);
	SREG &= ~(1<<7);
    transmit( ~(18+7+3+ 0x1E +0+2+0+2) ); //CHECKSUM
	set_direction_port(RECEIVE); 
	SREG |= (1<<7);
}

void test_set_return_status_level(){
    transmit(0xFF);
    transmit(0xFF);
    transmit(8); //ID = FE.
    transmit(0x04); //LENGTH = 4.
    transmit(0x03); //Instruction = write.
    transmit(0x10); //Parameter 1 --> Control table address = 0x19 => LED.
    transmit(0x02); //Parameter 2 --> data = 1 to be written. TURN ON
    transmit( ~(8 + 0x04 + 0x03 + 0x10 + 0x02) ); //CHECKSUM
}

void test_set_baud(){
    transmit(0xFF);
    transmit(0xFF);
    transmit(18); //ID = FE.
    transmit(0x04); //LENGTH = 4.
    transmit(0x03); //Instruction = write.
    transmit(0x04); //Parameter 1 --> Control table address = 0x19 => LED.
    transmit(0x01); //Parameter 2 --> data = 1 to be written. TURN ON
    transmit( ~(18 + 0x04 + 0x03 + 0x01 + 0x01) ); //CHECKSUM
}

int main(void)
{
	init_IO();
	usart_init(1000000);
	
	    
    /* test if data is received*/
    while(1){
<<<<<<< HEAD
		test_turn();
		volatile char id = test_receive_ID();
	}    
=======
		test_turn_off_LED();
		for (int i = 0; i<11512; i++);
		test_turn_on_LED();
		for (int i = 0; i<11512; i++);
    }    
>>>>>>> parent of 6fd476a... Show anders Commit

}