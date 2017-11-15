#include <avr/interrupt.h>


/*
Define interrupt vector for UART data received.

TODO: clean up code
*/
ISR(USART0_RX_vect){
	
	volatile uint8_t data_read = UDR0;
	volatile uint8_t id = data_read >> 4; 
	volatile uint8_t parameter = data_read & 0b0F; 
	
	
	switch(id) {
		
		//ask for status
		case 0b0000:
			/*	data_write consists of 8 bits where bit 7-4 is 
				status_id (ID) and bit 3-0 is parameter_ID (parameter) */
				
			//TODO: test
			
			volatile uint8_t status_id = 0; 
			volatile uint8_t status_parameter = 0; 
			volatile uint8_t data_write; 
			
			if (parameter == 0b0001){
				//ask for driving speed
				//TODO: implement
				
				int rotation_speed = get_traversal_status();
				status_id = 0b0010;
				
				if (rotation_speed >= 0){ 
					status_parameter = rotation_speed; 
				}
				/* 	left turn returns negative rotation speed. Inverts rotation speed and
					increases by 7 because parameter for left rotation speed 1 (-1) should 
					give back status_parameter 8 and so on. 								*/ 
				else if ( rotation_speed < 0) {
					status_parameter = (-(rotation_speed) + 7 ) 
				}
				
				data_write = ( status_id << 4 ) + status_parameter; //eller & status_parameter ? 
				UDR0 = data_write;
			}
		
			else if (parameter == 0b0010){
				//read driving direction and write to UART
				
				status_id = 0b0001;
				
				if (get_traversal_status() == 0){ status_parameter = 0b0000; } // idle
				else if (get_traversal_status() == 1){ status_parameter = 0b0001; } //forwards
				else if (get_traversal_status == -1){ status_parameter = 0b0010; } //backwards
				
				data_write = ( status_id << 4 ) + status_parameter; //eller & status_parameter ? 
				UDR0 = data_write; 
				
			}

			else if (parameter == 0b1111){
				//ask for armstatus
				//TODO: implement
			}
			
			break; 
		
		case 0b0001  :
			//TODO: test
		
			if (parameter == 0b0000){
				//robot idle
				set_traversal_speed(0);
			}
			else if (parameter == 0b0001){
				//robot drive forward
				set_traversal_speed(1);
			}
			else if (parameter == 0b0010){
				//robot drive backwards
				set_traversal_speed(-1);
			}
			
			break;
		
		case 0b0010  :
			//TODO: test
		
			/* 	check if we want to go right of left where dir = 0 is right 
				and dir = 1 is left 										*/
			int dir = parameter >> 3;
		
			if (dir == 0){
				set_turn_speed(parameter); 
			}
			else if (dir == 1){
				int left_turn_speed =  -(( parameter & 0b0111 ) + 0b0001);
				set_turn_speed(left_turn_speed);
			}
			
			break;
		
		case 0b1100  :
			
			//sätt motorhastighet för arm
			
			break; 
		
		case 0b1101  :
			
			// fråga om armen arbetar
			
			break; 
		
		case 0b1110  :
			
			// macro arm
			
			break;
		
		case 0b1111  :
			
			//rotering av arm
			
			break; 
		
		default: 
			break;
	}
	
	UDR0 = data_read;
}