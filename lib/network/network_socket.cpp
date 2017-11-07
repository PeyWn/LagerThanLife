#include <cstring>
#include <sstream>
#include <netdb.h>
#include <unistd.h>
#include "network_socket.h"

void NetworkSocket::close_socket() {
    close(sockfd);
}


int NetworkSocket::socket_write(string msg) {
    if (write(sockfd, (msg + DELIMITER).c_str(), strlen(msg.c_str()) + 1) < 0) {
        printf("ERROR writing to socket\n");
        return -1;
    }
    return 0;
}


string NetworkSocket::socket_read() {
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


void NetworkSocket::interpret_message(string msg_read) {
    string word;
    istringstream iss(msg_read);

    while (getline(iss, word, DELIMITER)) {
        thread_com->write_to_queue(word, 2);    // Relay message by writing to queue 2 - from socket to a module
    }

}


void NetworkSocket::main_loop()
{
    string msg_read = "";
    string msg_write = "";
    bool running = true;
    while(running == true) {

        //Read from queue 1 (from a module) and relay this info with socket_write
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

}
