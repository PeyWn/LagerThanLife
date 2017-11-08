/*
    Abstract class for functions that both client sockets and server sockets use
*/
#ifndef NETWORK_SOCKET_H
#define NETWORK_SOCKET_H

#include "string"
#include "interthreadcom.h"

class NetworkSocket {
    public:
        /*
            Writes, reads and interprets the messages that has been read
        */
        int write_read_interpret();

        /*
            Writes the input message to the socket

            string msg - The message that should be written

            Returns 0 if success, else -1
        */
        int socket_write(std::string msg);

        /*
            Reads a message from the socket and returns this message as a string
        */
        std::string socket_read();

        /*
            Split up a message using the delimiter and relay each word to CentralModule

            string msg_read - The message read that is to be splitted and relayed
        */
        void interpret_message(std::string msg_read);

    protected:
        const int PORT = 6000;
        std::string hostname = "192.168.43.245";

        int sockfd;
        InterThreadCom* thread_com;
        const char DELIMITER = '#';
};


#endif // NETWORK_SOCKET_H
