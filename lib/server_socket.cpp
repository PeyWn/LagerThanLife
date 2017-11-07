#include <cstring>
#include <unistd.h>
#include <netdb.h>
#include <fcntl.h>

#include "server_socket.h"

ServerSocket::ServerSocket(InterThreadCom* inter_thread_com) {
    thread_com = inter_thread_com;

    socklen_t clilen;
    int sockfd_init, newsockfd_init;
    struct sockaddr_in serv_addr, cli_addr;

    sockfd_init = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd_init < 0) {
        throw invalid_argument("ERROR opening socket\n");
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);

    if (bind(sockfd_init, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        throw invalid_argument("ERROR on binding, probably bad PORT\n");
    }

    listen(sockfd_init,5);
    clilen = sizeof(cli_addr);
    newsockfd_init = accept(sockfd_init, (struct sockaddr *) &cli_addr, &clilen);

    if (newsockfd_init < 0) {
        throw invalid_argument("ERROR on accept\n");
    }

    // Setting flag on socket on non-blocking mode
    if(fcntl(newsockfd_init, F_SETFL, fcntl(newsockfd_init, F_GETFL) | O_NONBLOCK) < 0) {
        throw invalid_argument("ERROR on setting O_NONBLOCK\n");
    }

    sockfd = newsockfd_init;
    close(sockfd_init);

}
