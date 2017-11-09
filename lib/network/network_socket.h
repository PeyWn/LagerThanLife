/*
    Abstract class for functions shared between client socket and server socket
*/
#ifndef NETWORK_SOCKET_H
#define NETWORK_SOCKET_H

#include "string"
#include "interthreadcom.h"

class NetworkSocket {
    protected:
        const char DELIMITER = '#';
        const int PORT = 6000;
        std::string hostname = "localhost";

        int sockfd;
        InterThreadCom* thread_com;

    public:
        /*
            Writes, reads and interprets a message.
            Messages are read from the queue from a module and written to
            the socket. Messages are read from the socket and then
            interpreted with the function interpret_message.

            Returns true if socket reading and writing success, else false
        */
        bool write_read_interpret();

        /*
            Writes the input message to the socket

            string msg - The message that should be written

            Returns true if success, else false
        */
        bool socket_write(std::string msg);

        /*
            Reads a message from the socket and returns thismessage as
            a string
        */
        std::string socket_read();

        /*
            Split up a message using the delimiter and relay each word
            to the module

            string msg_read - The message read that is to be splitted 
            and relayed
        */
        void interpret_message(std::string msg_read);
};

#endif // NETWORK_SOCKET_H
