#include <avr/io.h>
#include <avr/interrupt.h>
#include "wheel_control.h"
#include "globals.h"
#include "transmission.h"
#include "init_arm.h"
#include "uart_arm.h"
#include "coordinate.h"

int main(void)
{
	init_IO();
	usart_init(1000000);

	double servo[3];
	volatile double x = 25;
	volatile double y = 17;
	double ct = 5.323254219;
	int succes;
	

	
    while(1)
    {
		for (int i = 0; i < 100; i++)
		{
			y = y+1; 

			succes = calculate_angles(ct, x, y, servo);
		
			move_double_axis(2, 3, servo[0], SPEED_0);
			move_double_axis(4, 5, servo[1], SPEED_0);
			move_single_axis(6, servo[2], SPEED_0, WRITE_DATA); 
		}
    }
    return 0;
}
