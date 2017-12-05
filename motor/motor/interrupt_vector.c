#include <avr/interrupt.h>
#include "transmission.h"
#include "wheel_control.h"


/*
Define interrupt vector for UART data received.

TODO: clean up code
*/
ISR(USART0_RX_vect){
	
	volatile uint8_t data_read = UDR0;
	volatile uint8_t id = data_read >> 4; 
	volatile uint8_t parameter = data_read & 0b00001111; 
	
	
	switch(id) {
		
		//ask for status
		case 0b0000:
			/*	data_write consists of 8 bits where bit 7-4 is 
				status_id (ID) and bit 3-0 is parameter_ID (parameter) */
			;
			volatile uint8_t status_id = 0; 
			volatile uint8_t status_parameter = 0; 
			volatile uint8_t data_write; 
			
			if (parameter == 0b0001){
				//ask for turn status
				
				int rotation_speed = get_turn_status();
				status_id = 0b0010;
				
				if (rotation_speed >= 0){ 
					status_parameter = rotation_speed; 
				}
				/* 	left turn returns negative rotation speed. Inverts rotation speed and
					increases by 7 because parameter for left rotation speed 1 (-1) should 
					give back status_parameter 8 and so on. 								*/ 
				else if ( rotation_speed < 0) {
					status_parameter = (-(rotation_speed) + 7 );
				}
				
				data_write = ( status_id << 4 ) + status_parameter;
				UDR0 = data_write;
			}
		
			else if (parameter == 0b0010){
				//ask for driving status
				
				status_id = 0b0001;

				int traversal_speed = get_traversal_status();

				if(traversal_speed >= 0) { 
					status_parameter = traversal_speed;
				} 
				else {
					status_parameter = (traversal_speed * (-1)) + 7;
				}

				data_write = ( status_id << 4 ) + status_parameter;
				UDR0 = data_write; 
				
			}

			else if (parameter == 0b1111){
				//ask for armstatus
				//TODO: implement
			}
			
			break; 
		
		case 0b0001  :
		
			if (parameter == 0b0000){
				//robot idle
				set_traversal_speed(0);
			}

			int dir = parameter >> 3;

			if (dir == 0) {
				set_traversal_speed(parameter);
			}
			else {
			    set_traversal_speed(- parameter + 7);
			}
			
			break;
		
		case 0b0010  :
			/* 	check if we want to go right of left where dir = 0 is right 
				and dir = 1 is left 										*/
			;
			int drive_dir = parameter >> 3;
		
			if (drive_dir == 0){
				set_turn_speed(parameter); 
			}
			else if (drive_dir == 1){
				int left_turn_speed =  -(( parameter & 0b0111 ) + 0b0001);
				set_turn_speed(left_turn_speed);
			}
			
			break;
		
		case 0b1100  :
			//Set motor speed for arm
			//TODO implement

			break; 
		
		case 0b1101  :
			// control claw
            if(parameter == 0){
                grab();
            }
            else{
                release();
            }

			break; 
		case 0b1110  :
			// macro arm
            if(parameter == 0){
                //Stop all engines
                stop_all(); 

            }
            else if(parameter == 1){
                //Go to home position
                go_home_pos();
            }
            else if(parameter == 2){
                //Pickup ware
                pickup_standard();
            }
            else{
                //Put down ware
                putdown_standard();
            }
			break;
		
		case 0b1111  :
			//rotation of arm and single movements
            
			if (parameter == 0){ 
				//Start rotation of entire arm clock wise
				start_rotate_CW(); 
			}
			else if (parameter == 1){ 
				//Stop clock wise rotation of entire arm 
				stop_rotate_CW(); 
			}
			else if (parameter == 2){
				//Start rotation of entire arm counter clock wise 
				start_rotate_CCW(); 
			}
			else if (parameter == 3){ 
				//stop counter clock wise rotation of entire arm
				stop_rotate_CCW(); 
			}
			else if (parameter == 4){ 
				//start moving the arm upwards
				start_up(); 
			}
			else if (parameter == 5){
				//stop moving the arm upwards 
				//NOTE: there is no function in UI/central unit for calling this command,
				//however, currently the stop_up command calls the stop_all function
				stop_up(); 
			}
			else if (parameter == 6){ 
				//start moving the arm downwards 
				start_down(); 
			}
			else if (parameter == 7){ 
				//stop moving the arm downwards
				//NOTE: currently no function in central/UI for calling this fn
				stop_down(); 
			} 
			else if (parameter == 8){ 
				//start moving the arm towards its center body
				start_towards(); 
			}
			else if (parameter == 9){ 
				//stop moving the arm towards its center body
				//NOTE: currently no function in central/UI for calling this fn
				stop_towards(); 
			} 
			else if (parameter == 10){ 
				//start moving the arm away from its body
				start_away(); 
			}
			else if (parameter == 11){ 
				//stop moving the arm away from its body
				//NOTE: currently no function in central/UI for calling this fn
				stop_away();
			} 
			
			break; 
		default: 
			break;
	}
	
}

ISR(USART1_RX_vect)
{

}

ISR(USART1_TX_vect)
{
    
}

ISR(USART1_UDRE_vect)
{

}