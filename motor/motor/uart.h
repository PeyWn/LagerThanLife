/*
 * uart.h
 *
 * Created: 11/9/2017 11:38:56 AM
 *  Author: jesjo430
 */ 

/* Initializes the USART in Asynchronous Normal mode, with 0 parity bits, 1 stop bit and a baud-rate of 1M baud*/
void usart_init(int baud);

/* Send data via USART1 data register */
void usart_transmit( unsigned char data );

/* Receive data via USART1 data register */
unsigned char usart_receive(void); 
