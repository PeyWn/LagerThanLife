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
			//set id and parameter for sending back status 
			int status_id; 
			int status_parameter; 
		
			if (parameter == 0b0001){
				//sends turn speed
				//UDR0 = turn_status;
				status_id = 0b0010;
				
			}
			else if (parameter == 0b0010){
				//sends driving speed
				//UDR0 = traversal_status; 
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