#include <iostream>
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include "uart_handler.h"


UARTHandler::UARTHandler(string interface){
    uart_fd = open(interface.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);

    if (uart_fd == -1)
	{
		//Error when opening port
        cout << "Error when opening uart port." << endl;
	}

    struct termios options;
	tcgetattr(uart_fd, &options);
	options.c_cflag = B9600 | CS8 | CLOCAL | CREAD; //Baudrate of 9600
	options.c_oflag = 0;
	options.c_lflag = 0;
	options.c_iflag = IGNPAR;
	tcflush(uart_fd, TCIFLUSH);
	tcsetattr(uart_fd, TCSANOW, &options);
}

void UARTHandler::send_msg(int msg){
    //Cast to 8 bit data
    uart_msg to_send = (uart_msg) msg;

    //Send
    int bytes_written = write(uart_fd, &to_send, 1);
}

bool UARTHandler::read_msg(uart_msg buffer[]){
    int read_bytes = read(uart_fd, (void*)buffer, 1);

    if(read_bytes < 1){
        //read failed or nothing
        return false;
    }
    return true;
}
