/*
 * uart_arm.h
 *
 * Created: 2017-11-04 17:38:39
 *  Author: Jesper
 */ 

#define RECEIVE 0					 // Definition used when setting half duplex UART direction.
#define TRANSMIT 1					 // Definition used when setting half duplex UART direction.

/* Half duplex UART transmitter. Takes char (data) and sends via uart.c implementation, void*/
void transmit(unsigned char data);

/* Half duplex UART receiver. Takes no argument but returns char */ 
unsigned char receive(void);

/* Set value for UART direction on PIN for half-duplex control of robot arm */
void set_direction_port(int dir);