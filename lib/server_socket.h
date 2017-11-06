/**
    Implementation of CommunicationModule
    Handles communication with CentralModule and server side of socket communication
*/

#ifndef SERVER_SOCKET_H
#define SERVER_SOCKET_H

#include "interthreadcom.h"
#include "network_socket.h"

using namespace std;

class ServerSocket: public NetworkSocket {

public:
    ServerSocket(InterThreadCom* inter_thread_com);
};

#endif // SERVER_SOCKET_H