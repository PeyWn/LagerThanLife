#include <avr/io.h>
#include <avr/interrupt.h>
#include "wheel_control.h"
#include "init_arm.h"
#include "uart.h"
#include "globals.h"
#include "coordinate.h"

int main(void)
{
    init_IO();
    usart_init(0);
		
	while(!step_towards_pos(1, 0x1ff, pos_1, 0x0f));
		
    while(1)
    {
		
    }
	
    return 0;
}
