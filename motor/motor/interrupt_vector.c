#include <avr/interrupt.h>
#include "transmission.h"
#include "wheel_control.h"
#include "commands.h"


/*
Define interrupt vector for UART data received.
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
                stop_arm(); 

                if(do_putdown || do_pickup){
                    do_stop = true;
                }
            }
            else if(parameter == 1){
                //Go to home position
                go_home_pos();
            }
            else if(parameter == 2){
                //Pickup ware
                do_pickup = true;
            }
            else{
                //Put down ware
                do_putdown = true;
            }
			break;
		
		case 0b1111  :
			//Manual control of arm
            
			if (parameter == 0){ 
			    //Stop arm movements
                stop_arm();
			}
			else if (parameter == 1){ 
                //rotate entire arm clock wise
                axis_fwd(0);
			}
			else if (parameter == 2){
				//rotate entire arm counter clock wise
				axis_back(0);
			}
			else if (parameter == 3){ 
				//axis 1 forward
				axis_fwd(1);
			}
			else if (parameter == 4){ 
				//axis 1 back
				axis_back(1);
			}
			else if (parameter == 5){
				//axis 2 forward
				axis_fwd(2);
			}
			else if (parameter == 6){ 
				//axis 2 back
				axis_back(2);
			}
			else if (parameter == 7){ 
				//axis 3 forward
				axis_fwd(3);
			} 
			else if (parameter == 8){ 
				//axis 3 back
				axis_back(3);
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