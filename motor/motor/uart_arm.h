/*
 * uart_arm.h
 *
 * Created: 2017-11-04 17:38:39
 *  Author: Jesper
 */ 

/* Half duplex UART transmitter. Takes char (data) and sends via uart.c implementation, void*/
void transmit(unsigned char data);

/* Half duplex UART receiver. Takes no argument but returns char */ 
unsigned char receive(void);