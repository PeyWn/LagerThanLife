#include <unistd.h>
#include <netdb.h>
#include <fcntl.h>
#include <cstring>
#include <iostream>

#include "client_socket.h"

using namespace std;

ClientSocket::ClientSocket(InterThreadCom* inter_thread_com) {
    thread_com = inter_thread_com;

    new_connection();
}

bool ClientSocket::new_connection() {
    struct hostent *server;
    int sockfd_init;
    struct sockaddr_in serv_addr;

    sockfd_init = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd_init < 0) {
        return false;
    }

    server = gethostbyname(hostname.c_str());  // argument type for gethostbyname is char*
    if (server == NULL) {
        return false;
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(PORT);

    if (connect(sockfd_init,(struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        cout << "Connection failed" << endl;
        return false;
    }

    // Setting flag on socket on non-blocking mode
    if(fcntl(sockfd_init, F_SETFL, fcntl(sockfd_init, F_GETFL) | O_NONBLOCK) < 0) {
        return false;
    }

    sockfd = sockfd_init;
    connected = true;
    return true;
}

void ClientSocket::main_loop() {
    while(true) {
        if(connected) {
            if(write_read_interpret() < 0) {
                connected = false;
            }
        }
    }
}
