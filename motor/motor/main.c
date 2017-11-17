#include <avr/io.h>
#include <avr/interrupt.h>
#include "wheel_control.h"

#include "globals.h"
#include "init_arm.h"
#include "coordinate.h"

int main(void)
{
    /*
    init_wheel_control(0.3);
    update_wheel_control();     // test routine
    */

	//Conf UART

	//set rx to input, set tx to output
	DDRD = (0<<DDD0)|(1<<DDD1);

	UBRR0L = 0x67; //BAUDRATE 103

	//Set UART baudrate, activates Tx/Rx, activates interrupts for UART data recieved
	UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);

	//Enable global interrupts
	sei();
	
	/*
		const double PI 3.1415
		double servo[3];
		double x = 25;
		double y = 17;
		double ct = 5.323254219;
		int succes = calculate_angles(ct, x, y, servo);
	*/
	
    while(1)
    {

    }
    return 0;
}
