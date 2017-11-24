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
	
    while(1)
    {
		step_towards_pos(1,new_pos_1, cur_pos_1, 0x1f);
		step_towards_pos(1,new_pos_2, cur_pos_2, 0x1f);
		step_towards_pos(1,new_pos_3, cur_pos_3, 0x1f);
		step_towards_pos(1,new_pos_4, cur_pos_4, 0x1f);
		step_towards_pos(1,new_pos_5, cur_pos_5, 0x1f);
		step_towards_pos(1,new_pos_6, cur_pos_6, 0x1f);
		step_towards_pos(1,new_pos_7, cur_pos_7, 0x1f);
		step_towards_pos(1,new_pos_8, cur_pos_8, 0x1f);
    }
	
    return 0;
}
