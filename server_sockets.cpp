#include <unistd.h>
#include <netdb.h> 
#include <fcntl.h>
#include <sstream>
#include "server_sockets.h"

const int PORT = 6000;

CommunicationModule::CommunicationModule(InterThreadCom* inter_thread_com) {
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

int CommunicationModule::socket_write(string msg) {
    if (write(sockfd, (msg + DELIMITER).c_str(), strlen(msg.c_str()) + 1) < 0) {
        printf("ERROR writing to socket\n");
        return -1;
    }
    return 0;
}

string CommunicationModule::socket_read() {
    char buffer[256];
    bzero(buffer,256); // Clearing buffer before reading into it
    int n = read(sockfd, buffer, 255);
    string msg = buffer;

    if ((n == -1 && errno == EAGAIN) || n == 0) {       //Nothing to be read
        return "";   

    } else if (n < 0 ) {
        printf("ERROR reading from socket\n");
        return "";

    }
    return msg;
}


void CommunicationModule::interpret_message(string msg_read) {
    string word;
    istringstream iss(msg_read);

    while (getline(iss, word, DELIMITER)) {
        thread_com->write_to_queue(word, 2);    // Relay message by writing to queue 2, to CentralModule
    }

}


void CommunicationModule::main_loop()
{

    string msg_read = "";
    string msg_write = "";
    bool running = true;
    while(running == true) {

        //Read from queue 1, to CommunicationModule, and relay this info by socket_write
        msg_write = thread_com->read_from_queue(1);

        if (msg_write != "") {
            if (socket_write(msg_write) < 0) {
                running = false;
                break;
            }
        }
    
        msg_read = socket_read();

       if (msg_read != "") {
            interpret_message(msg_read);
        }
    }

        // close(sockfd);
}
