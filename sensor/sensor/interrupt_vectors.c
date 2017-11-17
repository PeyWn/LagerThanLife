#include <avr/interrupt.h>
#include "globals.h"
#include "ware_sensor.h"
#include "line_sensor.h"

/*
Define interrupt vector for ADC conversion complete.
*/
ISR(ADC_vect){
	adc_value = ADC;
    adc_done = true;
}

/*
Define interrupt vector for UART data received.
*/
ISR(USART_RXC_vect){
    uint8_t data_read = UDR;

    switch(data_read){
        case 1:
            //Return line center
            UDR = line_center;
        break;
        case 2:
            //Return line_state
            UDR = line_state;
        break;
        case 3:
            //Return ware_seen

            ;//Fix for C being bad
            uint8_t ware_return = (ware_seen[0] << 1) + ware_seen[1];
            UDR = ware_return;
        break;
        case 4:
            //Calibrate ware sensors
            calibrate_waresensor();
        break;
        case 5:
            //Calibrate line sensor for line
            calibrate_line();
        break;
        case 6:
            //Calibrate line sensor for floor
            calibrate_floor();
        break;
        default:
        break;
    }
}