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
	torque_enable(0xfe); 
	go_home_pos();
	move_axis(0, 0x1ff, 0x1f);
	
    while(1)
    {
		_delay_ms(100);
		if (update_pos() == 6)
		{
			IS_WORKING = 0; 
		}
		else
		{
			
		}
	}
	
    return 0;
}

int update_pos()
{
	return
	step_towards_pos(1 ,new_pos[0], cur_pos[0], 0x1f); +
	step_towards_pos(2 ,new_pos[1], cur_pos[1], 0x1f); +
	step_towards_pos(3 ,new_pos[2], cur_pos[2], 0x1f); +
	step_towards_pos(4 ,new_pos[3], cur_pos[3], 0x1f); +
	step_towards_pos(5 ,new_pos[4], cur_pos[4], 0x1f); +
	step_towards_pos(6 ,new_pos[5], cur_pos[5], 0x1f); 
}