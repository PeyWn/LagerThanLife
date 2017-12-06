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

volatile int new_pos[6];
volatile int cur_pos[6];
volatile int front_pos[6];
volatile int home_pos[6];

void init_cur_pos()
{
	go_home_pos();
	cur_pos[0] = new_pos[0];
	cur_pos[1] = new_pos[1];
	cur_pos[2] = new_pos[2];
	cur_pos[3] = new_pos[3];
	cur_pos[4] = new_pos[4];
	cur_pos[5] = 0x1ff;
	
	move_axis(1, cur_pos[1], 0x1f);
	move_axis(2, cur_pos[2], 0x1f);
	move_axis(3, cur_pos[3], 0x1f);
}

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
	IS_PICKUP = 0;
    IS_STOP = 0;
    IS_WORKING = 0;
    /*
	init_wheel_control();

    //set rx to input, set tx to output

    DDRD = (0<<DDD0)|(1<<DDD1);

    UBRR0L = 0x33; //BAUDRATE 33 = 19200

    //Set UART baudrate, activates Tx/Rx, activates interrupts for UART data recieved
    UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);

    //Enable global interrupts
    sei();
	*/
	

    //kill it with fire (may reprogram servos) torque_enable(0xfe);
    init_cur_pos(); 
	
    while(1)
    {
		
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
		
	if(!IS_STOP && update_pos()){
		IS_WORKING = 1;
	}
	else{
		IS_WORKING = 0;
	}
		
	if(IS_STOP)
	    {
		torque_disable_all();
		IS_WORKING = 0;
	    }
    }	
	
    return 0;
}

