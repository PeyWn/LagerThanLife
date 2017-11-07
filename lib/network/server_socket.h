/**
    Implementation of serverside of socket communication
*/

#ifndef SERVER_SOCKET_H
#define SERVER_SOCKET_H

#include "interthreadcom.h"
#include "network_socket.h"

#include <netdb.h>
#include <unistd.h>

class ServerSocket: public NetworkSocket {

public:
    socklen_t clilen;
    int sockfd_init, newsockfd_init;
    struct sockaddr_in serv_addr, cli_addr;

    ServerSocket(InterThreadCom* inter_thread_com);

    void new_connection();
};

#endif // SERVER_SOCKET_H