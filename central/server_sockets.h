/**
    Implementation of CommunicationModule
    Handles communication with CentralModule and server side of socket communication
*/

#ifndef SERVER_SOCKETS_H
#define SERVER_SOCKETS_H

#include "interthreadcom.h"

const char DELIMITER = '#';

using namespace std;

class CommunicationModule {

private:
    int sockfd;
    InterThreadCom* thread_com;

    /*
        Writes the input message to the socket.

        string msg - The message that should be written.
        
        Returns 0 if success, else -1
    */
    int socket_write(string msg);

    /*
        Reads a message from the socket and returns this message as a string.
    */
    string socket_read();

    /*
        Split up a message using the delimiter and relay each word to CentralModule

        string msg_read - The message read that is to be splitted and relayed
    */
    void interpret_message(string msg_read);

public:
    CommunicationModule(InterThreadCom* inter_thread_com);

    /*
        The main loop for CommunicationModule that will check for new messages and relay them.
        Messages from CentralModule will be relayed by writing to the socket.
        Messages from the socket will be relayed to CentralModule.
    */
    void main_loop();

};

#endif // SERVER_SOCKETS_H