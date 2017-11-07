/**
    Implementation of CommunicationModule
    Handles communication with CentralModule and server side of socket communication
*/

#ifndef CLIENT_SOCKET_H
#define CLIENT_SOCKET_H

#include "interthreadcom.h"
#include "network_socket.h"

using namespace std;

class ClientSocket: public NetworkSocket {

public:
    ClientSocket(InterThreadCom* inter_thread_com);
};

#endif // CLIENT_SOCKETS_H