/**
    Implementation of serverside of socket communication
*/

#ifndef SERVER_SOCKET_H
#define SERVER_SOCKET_H

#include "interthreadcom.h"
#include "network_socket.h"

using namespace std;

class ServerSocket: public NetworkSocket {

public:
    ServerSocket(InterThreadCom* inter_thread_com);

    new_connection();
};

#endif // SERVER_SOCKET_H