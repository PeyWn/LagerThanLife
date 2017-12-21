#ifndef UART_H
#define UART_H

/*  Initializes the UART communication with the arm in Asynchronous Normal mode, with 0 parity
    bits, 1 stop bit and a baud-rate of 1M baud                                                 */
void usart1_init();

/*  Initializes UART communication with the central unit                                        */
void usart0_init();

/*  Send data via USART1 data register                                                          */
void usart_transmit( unsigned char data );

/*  Receive data via USART1 data register                                                       */
unsigned char usart_receive(void);

#endif // UART_H
