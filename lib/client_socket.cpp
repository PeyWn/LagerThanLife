#include <unistd.h>
#include <netdb.h> 
#include <fcntl.h>

#include "client_socket.h"

using namespace std;

ClientSocket::ClientSocket(InterThreadCom* inter_thread_com) {
    thread_com = inter_thread_com;

    int sockfd_init;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    sockfd_init = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd_init < 0) {
        throw invalid_argument("ERROR opening socket\n");
    }

    string temp = "localhost";

    server = gethostbyname(temp.c_str());  // hostname takes char *hostname
    if (server == NULL) {
        throw invalid_argument("ERROR, host not found\n");
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(PORT); 

    if (connect(sockfd_init,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) {
        throw invalid_argument("ERROR connecting\n");
    }

    // Setting flag on socket on non-blocking mode
    if(fcntl(sockfd_init, F_SETFL, fcntl(sockfd_init, F_GETFL) | O_NONBLOCK) < 0) {
        throw invalid_argument("ERROR on setting O_NONBLOCK\n");
    }

    sockfd = sockfd_init;
}