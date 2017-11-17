#include <avr/io.h>
#include <avr/interrupt.h>
#include "wheel_control.h"
#include "globals.h"
#include "transmission.h"
#include "init_arm.h"
#include "uart_arm.h"

int main(void)
{
	init_IO();
	usart_init(1000000);

    while(1)
    {

    }
    return 0;
}
