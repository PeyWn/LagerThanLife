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
    
    /* INITIALIZE WHEEL_CONTROL */
    init_wheel_control();  
    
    while(1)
    {

    }
    return 0;
}
