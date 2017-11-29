#include "globals.h"    //F_CPU define first
#include <avr/io.h>
#include <avr/interrupt.h>

#include "wheel_control.h"
#include "init_arm.h"
#include "uart.h"
#include "coordinate.h"
#include "commands.h"

/* was not included */
#include "transmission.h"   
#include "receive.h"  
/*------------------*/   

volatile int IS_WORKING; //Flag for indication that the arm is moving
volatile int IS_STOP;
volatile int IS_PICKUP;
volatile int IS_PUTDOWN; 

volatile int new_pos[6];
volatile int cur_pos[6];
volatile int front_pos[6];
volatile int home_pos[6];

int update_pos()
{
	return
	step_towards_pos(0 , 0x1f) +
	step_towards_pos(1 , 0x1f) +
	step_towards_pos(2 , 0x1f) +
	step_towards_pos(3 , 0x1f) +
	step_towards_pos(4 , 0x1f) +
	step_towards_pos(5 , 0x1f); 
}

int compare_arrays(int arr1[], int arr2[], int len)
{
	for (int i = 0; i < len; i++)
	{
		if (arr1[i] != arr2[i])
		{
			return 0;
		}
	}
	return 1; 	
}

int main(void)
{
    init_IO();
    usart_init(0);
	torque_enable(0xfe);
	IS_PICKUP = 0;
	IS_STOP = 0;
	IS_WORKING = 0; 
	go_home_pos(); 
    
	/*
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
    
	*/
	
    while(1)
    {
		cur_pos[0] += 1; 
		
		
		if(IS_PICKUP || IS_PUTDOWN) 
		{
			go_pos_front();
			if (compare_arrays(cur_pos, front_pos, 6))
			{
				if (IS_PUTDOWN)
				{
					release();
				}
				grab();
				go_home_pos();
			}
		}
		
		
		if(update_pos() == 8)
		{
			IS_WORKING = 0;
		}
		if(IS_STOP)
		{
			torque_disable_all();
		}
		
    }
	
    return 0;
}

