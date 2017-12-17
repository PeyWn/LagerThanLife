#include <cstring>
#include <unistd.h>
#include <netdb.h>
#include <fcntl.h>
#include <iostream>
#include <thread>

#include "server_socket.h"

ServerSocket::ServerSocket(InterThreadCom* inter_thread_com) {
    thread_com = inter_thread_com;

    sockfd_init = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd_init < 0) {
        throw std::invalid_argument("ERROR opening socket\n");
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);

    /* Setting socket port reuseable */
    int on = 1;
    setsockopt (sockfd_init, SOL_SOCKET, SO_REUSEADDR, &on, sizeof (on));

    if (bind(sockfd_init, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        throw std::invalid_argument("ERROR on binding, probably bad PORT\n");
    }

    if (!new_connection()) {
        throw std::invalid_argument("Error setting up connection");
    }

}

bool ServerSocket::new_connection() {
    thread_com->write_to_queue("Listening for new connection...", FROM_SOCKET);

    listen(sockfd_init,5);
    clilen = sizeof(cli_addr);
    newsockfd_init = accept(sockfd_init, (struct sockaddr *) &cli_addr, &clilen);

    if(newsockfd_init < 0) {
        return false;
    }

    /* Setting flag on socket to non-blocking mode */
    if(fcntl(newsockfd_init, F_SETFL, fcntl(sockfd_init, F_GETFL) | O_NONBLOCK) < 0) {
        return false;
    }

    sockfd = newsockfd_init;

    thread_com->write_to_queue("Connected", FROM_SOCKET);
    return true;
}


void ServerSocket::main_loop() {
    while(true) {
        write_read_interpret();
    }
}
