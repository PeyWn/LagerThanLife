#include <avr/io.h>
#include <avr/interrupt.h>
#include "wheel_control.h"
#include "globals.h"
#include "transmission.h"
#include "init_arm.h"
#include "uart_arm.h"

#include "globals.h"
#include "init_arm.h"
#include "coordinate.h"

int main(void)
{
	init_IO();
	usart_init(1000000);

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
