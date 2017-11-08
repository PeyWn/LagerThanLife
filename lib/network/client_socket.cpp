#include <unistd.h>
#include <netdb.h>
#include <fcntl.h>
#include <cstring>
#include <iostream>

#include "client_socket.h"

using namespace std;

ClientSocket::ClientSocket(InterThreadCom* inter_thread_com) {
    thread_com = inter_thread_com;

    if(new_connection() == -1) {
        throw invalid_argument("ERROR connecting");
    }
}

int ClientSocket::new_connection() {
    struct hostent *server;
    int sockfd_init;
    struct sockaddr_in serv_addr;

    sockfd_init = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd_init < 0) {
        return -1;
    }

    server = gethostbyname(hostname.c_str());  // argument type for gethostbyname is char*
    if (server == NULL) {
        return -1;
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(PORT);

    if (connect(sockfd_init,(struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        return -1;
    }

    // Setting flag on socket on non-blocking mode
    if(fcntl(sockfd_init, F_SETFL, fcntl(sockfd_init, F_GETFL) | O_NONBLOCK) < 0) {
        return -1;
    }

    sockfd = sockfd_init;
    return 0;
}

void ClientSocket::main_loop() {
    while(true) {
        if(write_read_interpret() < 0) {
            thread_com->write_to_queue(disconnect_msg,2);
            write_read_interpret(); //Extra to print disconnect_msg
            while(new_connection() < 0) {

            }
            thread_com->write_to_queue(connected_msg,2);
        }
    }
}
