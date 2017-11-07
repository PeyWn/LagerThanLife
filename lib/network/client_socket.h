/**
    Implementation of clientside of socket communication
*/

#ifndef CLIENT_SOCKET_H
#define CLIENT_SOCKET_H

#include <unistd.h>
#include <netdb.h>
#include "interthreadcom.h"
#include "network_socket.h"

using namespace std;

class ClientSocket: public NetworkSocket {

public:
    ClientSocket(InterThreadCom* inter_thread_com);

    void new_connection();
};

#endif // CLIENT_SOCKETS_H