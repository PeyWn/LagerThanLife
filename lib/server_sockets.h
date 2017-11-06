/**
    Implementation of CommunicationModule
    Handles communication with CentralModule and server side of socket communication
*/

#ifndef SERVER_SOCKETS_H
#define SERVER_SOCKETS_H

#include "interthreadcom.h"
#include "network_sockets.h"

using namespace std;

class ServerSockets: public NetworkSockets {

public:
    ServerSockets(InterThreadCom* inter_thread_com);
};

#endif // SERVER_SOCKETS_H