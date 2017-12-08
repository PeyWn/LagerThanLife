#include <iostream>
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <stdexcept.h>
#include "uart_handler.h"

UARTHandler::UARTHandler(string interface){
    uart_fd = open(interface.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);

    if (uart_fd == -1)
	{
		throw invalid_argument("ERROR creating uart connection for interface: " + interface + "\n");
	}

    //Set up UART option with termios
    struct termios options;
	tcgetattr(uart_fd, &options);
	options.c_cflag = B19200 | CS8 | CLOCAL | CREAD; //Baudrate of 9600
	options.c_oflag = 0;
	options.c_lflag = 0;
    options.c_iflag = IGNPAR;

    tcflush(uart_fd, TCIFLUSH); //Flush input buffer
	tcsetattr(uart_fd, TCSANOW, &options);
}

void UARTHandler::send_msg(int msg){
    //Cast to 8 bit data
    uart_msg to_send = (uart_msg) msg;

    //Send
    int bytes_written = write(uart_fd, &to_send, 1);
}

int UARTHandler::read_msg(){
    uart_msg buffer[1];
    int read_bytes = 0;

    while(read_bytes < 1){ //read failed or nothing
        read_bytes = read(uart_fd, (void*)buffer, 1);
    }

    return (int)buffer[0];
}
