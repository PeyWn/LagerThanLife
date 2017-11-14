#include <avr/interrupt.h>


/*
Define interrupt vector for UART data received.
*/
ISR(USART0_RX_vect){
	volatile uint8_t data_read = UDR0;
	int id = data_read >> 4; 
	int parameter = data_read & 0F; 
	
	
	switch(id) {

		case 0b0000:
			/*	data_write consists of 8 bits where bit 7-4 is 
				status_id (ID) and 3-0 is parameter_ID (parameter) */
			int status_id; 
			int status_parameter; 
			volatile uint8_t data_write; 
		
			if (parameter == 0b0001){
				//read turn speed and write to UART
				//TODO: test
							
				status_id = 0b0010;
				
				if (read_turn_status() == 0){ status_parameter = 0000; }
				else if (read_turn_status() == 1){ status_parameter = 0001; }
				else if (read_turn_status == -1){ status_parameter = 0010; }
				
				data_write = ( status_id >> 4 ) + status_parameter; 
				
			}
			else if (parameter == 0b0010){
				//sends driving speed
				//TODO: som ovanför
			}
			else if (parameter == 0b1111){
				//begär armstatus
			}
			
			break; 
		
		case 0b0001  :
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

			set_turn_speed(parameter);
		
			break;
		
		case 0b1100  :
			
			//sätt motorhastighet för arm
			//ex: sätt_motorhastighet_för_arm(parameter)
			
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