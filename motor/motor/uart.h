/*This function initializes the USART in Asynchronous Normal mode.*/
void usart_init(void);

/* Function to send data */
void usart_transmit( unsigned char data );

/* Function to receive data */
unsigned char uart_recieve(void); 
