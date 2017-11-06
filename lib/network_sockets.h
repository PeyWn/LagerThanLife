#ifndef NETWORK_SOCKETS_H
#define NETWORK_SOCKETS_H

#include "string"
#include "interthreadcom.h"

const int PORT = 6000;
const char DELIMITER = '#';

using namespace std;

class NetworkSockets {
    
    public:
        int sockfd;
        InterThreadCom* thread_com;

        /*
            The main loop that will check for new messages and relay them
        */
        void main_loop();

        /*
            Writes the input message to the socket
    
            string msg - The message that should be written
            
            Returns 0 if success, else -1
        */
        int socket_write(string msg);
    
        /*
            Reads a message from the socket and returns this message as a string
        */
        string socket_read();
    
        /*
            Split up a message using the delimiter and relay each word to CentralModule
    
            string msg_read - The message read that is to be splitted and relayed
        */
        void interpret_message(string msg_read);
    
    };


#endif // NETWORK_SOCKETS_H