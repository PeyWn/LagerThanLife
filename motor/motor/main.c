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

	volatile double CT_angle = 5.323254219;
	volatile double Tx = 25;    // target Y for claw
	volatile double Ty = 5;    // target X for claw
	volatile double servo[3];   
	
	int test = calculate_angles(CT_angle, Tx, Ty, &servo);
	
	if(test){
        //torque_enable(0xFE); // OBS!!! Base-servo starts turning...
        volatile int angle_a = round(servo[0]);
        volatile int angle_b = round(servo[1]); 
        volatile int angle_c = round(servo[2]);
        move_double_axis(4, 5, angle_b, 0x0F);
		move_double_axis(2, 3, angle_a, 0x0F);
		move_single_axis(6, angle_c, 0x0F, WRITE_DATA);
        
		/*move_double_axis(2,3,(char)servo[0], 0x0F);
		move_double_axis(4,5,(char)servo[1], 0x0F);
		move_single_axis(6, (char)servo[2], 0x0F, WRITE_DATA);
		*/	
	}
	
    while(1)
    {
    }
    return 0;
}
