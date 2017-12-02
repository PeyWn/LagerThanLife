#include <avr/io.h>
#include <avr/interrupt.h>
#include "wheel_control.h"
#include "init_arm.h"
#include "uart.h"

int main(void)
{
	/* CONFIGURE UART */
    
	/* set rx to input, set tx to output */
	DDRD = (0<<DDD0)|(1<<DDD1);
    
    init_IO();
    usart_init(0);

	UBRR0L = 0x33; //BAUDRATE 33 = 19200

	//Set UART baudrate, activates Tx/Rx, activates interrupts for UART data recieved
	UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);
	
    /* Enable global interrupts */
	sei();
    
    /* INITIALIZE WHEEL_CONTROL - OBS! REMOVE TESTING-STATEMENTS */
    
    init_wheel_control();
    
    /* testing-statements */
    if(0){
        set_traversal_speed(-7);
        set_turn_speed(-7);
        set_turn_speed(7);
        set_traversal_speed(-3);
        set_turn_speed(-7);
        set_turn_speed(7);
        set_turn_speed(-4);
        set_turn_speed(4);
        set_traversal_speed(-7);
        set_turn_speed(-4);
        set_turn_speed(4);
    }    
    
    while(1)
    {

    }
    return 0;
}
