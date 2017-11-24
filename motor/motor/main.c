#include "globals.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "wheel_control.h"
#include "init_arm.h"
#include "uart.h"
#include "coordinate.h"

int main(void)
{
    init_wheel_control(0.3);



	//Conf UART

	//set rx to input, set tx to output
	DDRD = (0<<DDD0)|(1<<DDD1);

    init_IO();
    usart_init(0);

	UBRR0L = 0x67; //BAUDRATE 103

	//Set UART baudrate, activates Tx/Rx, activates interrupts for UART data recieved
	UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);

	//Enable global interrupts
	sei();

	volatile double CT_angle = 0; //5.323254219;
	volatile double Tx;    // target Y for claw
	volatile double Ty;    // target X for claw
	volatile double servo[3];   
	
	volatile int test;
	volatile int angle_a;
	volatile int angle_b;
	volatile int angle_c; 
	
	Tx = 30;
	Ty = 31;
	test = calculate_angles(CT_angle, Tx, Ty, &servo);
	angle_a = round(servo[0]);
	angle_b = round(servo[1]);
	angle_c = round(servo[2]);
	
	if(test){
        //torque_enable(0xFE); // OBS!!! Base-servo starts turning...
		move_double_axis(2,3,angle_a, 0x0F);
		move_double_axis(4,5,angle_b, 0x0F);
		move_single_axis(6, angle_c, 0x0F, WRITE_DATA);
	}
	
	Tx = 20;
	Ty = 30;
	test = calculate_angles(CT_angle, Tx, Ty, &servo);
	angle_a = round(servo[0]);
	angle_b = round(servo[1]);
	angle_c = round(servo[2]);
	
	if(test){
        //torque_enable(0xFE); // OBS!!! Base-servo starts turning...
		move_double_axis(2,3,angle_a, 0x0F);
		move_double_axis(4,5,angle_b, 0x0F);
		move_single_axis(6, angle_c, 0x0F, WRITE_DATA);
	}
	
	Tx = 20;
	Ty = 35;
	test = calculate_angles(CT_angle, Tx, Ty, &servo);
	angle_a = round(servo[0]);
	angle_b = round(servo[1]);
	angle_c = round(servo[2]);
	
	if(test){
        //torque_enable(0xFE); // OBS!!! Base-servo starts turning...
		move_double_axis(2,3,angle_a, 0x0F);
		move_double_axis(4,5,angle_b, 0x0F);
		move_single_axis(6, angle_c, 0x0F, WRITE_DATA);
	}

	
    while(1)
    {
    }
    return 0;
}
