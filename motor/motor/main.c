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
    init_IO();
    usart1_init(0);
    usart0_init();
    init_wheel_control();

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
