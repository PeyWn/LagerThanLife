
#include "globals.h"    //F_CPU define first

#include <avr/io.h>
#include <avr/interrupt.h>

#include "wheel_control.h"
#include "init_arm.h"
#include "uart.h"
#include "coordinate.h"

/* was not included */
#include "transmission.h"   
#include "receive.h"  
/*------------------*/      

int main(void)
{
    /*  note -- servo IDs
        dual axis:
            2,3
            4,5
        single axis:
            8
            7
            6
            2
            1
    */
    
    init_IO();
    usart_init(0);
	torque_enable(0xfe); 
    
    
    volatile int received_data;
    
    volatile int   test = 0;
    
    received_data = read_word(1, PRESENT_POS_ADDRESS);
    test = received_data;
    
	move_axis(0, 0x200, 0x1F);
    
    received_data = read_word(1, PRESENT_POS_ADDRESS);
    test = received_data;
    
    move_axis(0, 0x100, 0x1F);
    
    received_data = read_word(1, PRESENT_POS_ADDRESS);
    test = received_data;
    test = 0;
    
    
    while(1)
    {
		//while(!step_towards_pos(1, 0x1ff, 0xf0));
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