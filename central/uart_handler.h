#ifndef UART_HANDLER_H
#define UART_HANDLER_H

#include <string>
using namespace std;

typedef char uart_msg;

class UARTHandler{
private:
    int uart_fd;
public:

    /*
    Create a new UARThandler that talks to the given interface.

    interface - a string with the name of the interface this instance
                should use for communication. Usually ttyUSB0 or ttyUSB1
    */
    UARTHandler(string interface);

    /*
    Send the given message through the UART connection

    msg - the integer (between 0 and 254) to be sent over the uart connection
    */
    void send_msg(int msg);

    /*
    Wait until a message is recieved over the uart connection and
    return the recieved message.

    return - the message that has been received over the uart connection.
    */
    int read_msg();
};

#endif /* UART_HANDLER_H */
