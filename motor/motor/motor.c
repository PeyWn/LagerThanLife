/*
 * motor.c
 *
 * Created: 11/1/2017 8:55:44 AM
 *  Author: jakno732
 */ 


#include <avr/io.h>
#include "wheel_control.h"

int main(void)
{
    
    init_wheel_control(0.3);
    
    //set_traversal_speed(1);
    
    update_wheel_control();

    while(1)
    {
        
    }
    return 0;
}