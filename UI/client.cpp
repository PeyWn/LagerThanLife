#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <iostream>
#include <fcntl.h>
#include <sstream>

using namespace std;

const char DELIMITER = '#';

int setup_client_sockets(char *hostname, int port){
    int sockfd_init, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    sockfd_init = socket(AF_INET, SOCK_STREAM, 0);  // Create a new socket file descriptor
    if (sockfd_init < 0) {
        printf("ERROR opening socket");
        return -1;
    }

    server = gethostbyname(hostname);
    if (server == NULL) {
        printf("ERROR, host not found\n");
        return -1;
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;

    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);

    serv_addr.sin_port = htons(port); 

    n = connect(sockfd_init,(struct sockaddr *) &serv_addr,sizeof(serv_addr));
    if (n < 0) {
        printf("ERROR connecting\n");
        return -1;
    }

    // Setting flag on socket on non-blocking mode
    if(fcntl(sockfd_init, F_SETFL, fcntl(sockfd_init, F_GETFL) | O_NONBLOCK) < 0) {
        return -1;
    }

    return sockfd_init;
}

int socket_write(string msg, int sockfd) {
    if (write(sockfd, (msg + DELIMITER).c_str(), strlen(msg.c_str()) + 1) < 0) {
        printf("ERROR writing to socket");
        return -1;
    }
    return 0;
}

string socket_read(int sockfd) {
    char buffer[256];
    bzero(buffer,256); // Clearing buffer before reading into it
    int n = read(sockfd,buffer,255);
    string msg = buffer;

    if ((n == -1 && errno == EAGAIN) || n == 0) {
        printf("Tried to read but got nothing\n");
        return "";   

    } else if (n < 0 ) {
        printf("ERROR reading from socket\n");
        return "";

    }
    return msg;
}

int interpret_message(string msg_read) {
    string word;
    istringstream iss(msg_read);

    while (getline(iss, word, DELIMITER)) {
        cout << "Message read: " << word << "\n";

        if (word == "exit") {
            return -1;
        }
    }

    return 0;
}

int main(int argc, char *argv[])
{
    int sockfd;

    if (argc != 3) {
        printf("Error input. First argument IP-adress. Second port.\n");
        return -1;
    }

    if ((sockfd = setup_client_sockets(argv[1], atoi(argv[2]))) < 0) {
        return -1;
    }


    string msg_read;
    string msg_write;
    bool running = true;
    while(running == true) {

        printf("Please enter the message: ");
        getline(cin, msg_write);
        if (socket_write(msg_write, sockfd) < 0) {
            running = false;
            break;
        }
    
        string msg_read = socket_read(sockfd);

        if (interpret_message(msg_read) < 0) {
            running = false;
            break;
        }

    }

    close(sockfd);
    printf("Socket closed\n");
    return 0;
}