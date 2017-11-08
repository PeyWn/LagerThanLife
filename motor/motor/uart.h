/*This function initializes the USART in Asynchronous Normal mode.*/
void usart_init(int baud);

/* Function to send data */
void usart_transmit( unsigned char data );

/* Function to receive data */
unsigned char usart_receive(void); 
