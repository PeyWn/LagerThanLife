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

    int on = 1;
    setsockopt (sockfd_init, SOL_SOCKET, SO_REUSEADDR, &on, sizeof (on));

    if (bind(sockfd_init, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        throw std::invalid_argument("ERROR on binding, probably PORT in use\n");
    }

    new_connection();

}

void ServerSocket::new_connection() {
    std::cout << "Listening for new connection" << std::endl;
    
    listen(sockfd_init,5);
    clilen = sizeof(cli_addr);
    newsockfd_init = accept(sockfd_init, (struct sockaddr *) &cli_addr, &clilen);

    if (newsockfd_init < 0) {
        throw std::invalid_argument("ERROR on accept\n");
    }

    // Setting flag on socket on non-blocking mode
    if(fcntl(newsockfd_init, F_SETFL, fcntl(newsockfd_init, F_GETFL) | O_NONBLOCK) < 0) {
        throw std::invalid_argument("ERROR on setting O_NONBLOCK\n");
    }

    sockfd = newsockfd_init;
    std::cout << "New connection made" << std::endl;

}


void ServerSocket::main_loop() {
    while(true) {
        write_read_interpret();
    }
}