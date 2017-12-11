#include "globals.h"    //F_CPU define first
#include <avr/io.h>
#include <avr/interrupt.h>

#include "wheel_control.h"
#include "init_arm.h"
#include "uart.h"
#include "commands.h"

#include "transmission.h"   
#include "receive.h" 

volatile int front_pos[6];
volatile int home_pos[6];

volatile bool do_stop = false;
volatile bool do_pickup = false;
volatile bool do_putdown = false;

int main(void)
{
    /* CONFIGURE UART */

    init_IO();
    usart_init(0);
    
    init_wheel_control();

    /* DDRD = (0<<DDD0)|(1<<DDD1); */ 
    DDRD |=  (1<<DDD1);
    DDRD &= ~(1<<DDD0);

    UBRR0L = 0x33; //BAUDRATE 33 = 19200

    //Set UART baudrate, activates Tx/Rx, activates interrupts for UART data recieved
    UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);

    //Enable global interrupts
    sei();

    while(1){

        if(do_pickup){
            pickup_standard();
            do_putdown = false;
            do_pickup = false;
        }
        else if(do_putdown){
            putdown_standard();
            do_putdown = false;
            do_pickup = false;
        }
    }
}

