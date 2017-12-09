#include "globals.h"    //F_CPU define first
#include <avr/io.h>
#include <avr/interrupt.h>

#include "wheel_control.h"
#include "init_arm.h"
#include "uart.h"
#include "coordinate.h"
#include "commands.h"

#include "transmission.h"   
#include "receive.h" 

volatile int IS_WORKING; //Flag for indication that the arm is moving
volatile int IS_STOP;
volatile int IS_PICKUP;
volatile int IS_PUTDOWN; 

volatile int front_pos[6];
volatile int home_pos[6];

int main(void)
{
    init_IO();
    usart_init(0);
	IS_PICKUP = 0;
	IS_PUTDOWN = 0;
    IS_STOP = 0;
    IS_WORKING = 0;
    
	init_wheel_control();

    //set rx to input, set tx to output

    /* DDRD = (0<<DDD0)|(1<<DDD1); */ 
    DDRD |=  (1<<DDD1);
    DDRD &= ~(1<<DDD0);

    UBRR0L = 0x33; //BAUDRATE 33 = 19200

    //Set UART baudrate, activates Tx/Rx, activates interrupts for UART data recieved
    UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);

    //Enable global interrupts
    sei();

    while(1)
    {
        
    }
}

