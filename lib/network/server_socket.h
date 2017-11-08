/**
    Implementation of serverside of socket communication
*/

#ifndef SERVER_SOCKET_H
#define SERVER_SOCKET_H

#include <netdb.h>
#include <unistd.h>
#include "interthreadcom.h"
#include "network_socket.h"

class ServerSocket: public NetworkSocket {

public:
    socklen_t clilen;
    int sockfd_init, newsockfd_init;
    struct sockaddr_in serv_addr, cli_addr;

    ServerSocket(InterThreadCom* inter_thread_com);

    /*
        Listens for a new connection to the socket
        and update sockfd to the last connected
    */
    bool new_connection();

    /*
        Main loop for server_socket. Read, writes and interpret
        messages using function write_read_interpret.
    */
    void main_loop();
};

#endif // SERVER_SOCKET_H