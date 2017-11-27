/*
 * uart_arm.h
 *
 * Created: 2017-11-04 17:38:39
 *  Author: Jesper
 */ 

#define RECEIVE 0	// Definition used when setting half duplex UART direction.
#define TRANSMIT 1	// Definition used when setting half duplex UART direction.

/* Changes the output on direction port to int dir, used for half-duplex uart */
void set_direction_port(int dir);

/* UART transmitter. Changes direction port to transmit and sends char (data) via USART1 */
void transmit(unsigned char data);

/* UART receiver. Changes direction port to receive and returns received char */ 
unsigned char receive(void);

/* Reads data register of receive to release receive flag of uart transmit */ 
void flush_UDR(); 