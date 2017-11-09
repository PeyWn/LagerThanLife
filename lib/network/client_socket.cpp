#include <unistd.h>
#include <netdb.h>
#include <fcntl.h>
#include <cstring>
#include <iostream>
#include <signal.h>

#include "client_socket.h"

using namespace std;

ClientSocket::ClientSocket(InterThreadCom* inter_thread_com) {
    thread_com = inter_thread_com;

    connected = new_connection();
}

bool ClientSocket::new_connection() {
    struct hostent *server;
    int sockfd_init;
    struct sockaddr_in serv_addr;

    sockfd_init = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd_init < 0) {
        return false;
    }

    // Argument type for gethostbyname is char*
    server = gethostbyname(hostname.c_str());
    if (server == NULL) {
        close(sockfd_init);
        return false;
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(PORT);

    if (connect(sockfd_init,(struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        close(sockfd_init);
        return false;
    }

    // Signal SIGPIPE will be ignored and handled manually
	signal(SIGPIPE, SIG_IGN);

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

        if (connected == true) {
            if(write_read_interpret() == false) {
                connected = false;
                
            }
        }


        if(connected == false) {
            thread_com->write_to_queue(disconnect_msg, FROM_SOCKET);
            while(new_connection() == false) {
            }
            thread_com->write_to_queue(connected_msg, FROM_SOCKET);
            
        }
        
    }
}

bool ClientSocket::is_connected() {
    return connected;
}

