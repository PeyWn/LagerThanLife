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
	
	//_delay_ms(100);
	move_axis(1, cur_pos[1], 0x1f);
	//_delay_ms(100);
	move_axis(2, cur_pos[2], 0x1f);
	//_delay_ms(100);
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

volatile int pos;


void get_servo_status(){
    flush_UDR1_receive();
    Packet data;
    char data1, data2;
    
    read_byte(4, PRESENT_POS_ADDRESS);
    receive_status_packet(&data);
    data1 = data.params[0];
    
    flush_UDR1_receive();
    
    read_byte(4, PRESENT_POS_ADDRESS+1);
    receive_status_packet(&data);
    data2 = data.params[0];
    
    pos = ((((short)data1)<<8) | data2);
    
    volatile char test = 0;
    
    
}

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
	
    //read_byte(4, PRESENT_POS_ADDRESS);
    //receive_status_packet();
    
    //get_servo_status();
    
    //write_byte(4, LED_ADDRESS, 1, WRITE_DATA);
    
    //ping_servo(4);
    //receive_status_packet();
    get_servo_status();
    
	
    while(1)
    {

    }
}

