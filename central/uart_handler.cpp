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
	tcflush(uart_fd, TCIFLUSH);
	tcsetattr(uart_fd, TCSANOW, &options);
}

void UARTHandler::send_msg(int msg){
    uart_msg to_send = (uart_msg) msg;

    cout << "msg:" << msg << endl;

    if(uart_fd != -1){
        int bytes_written = write(uart_fd, &to_send, 1);
        cout << bytes_written << "bytes written." << endl;
    }
}

int UARTHandler::read_msg(){

}
