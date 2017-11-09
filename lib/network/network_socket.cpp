#include <cstring>
#include <sstream>
#include <netdb.h>
#include <unistd.h>
#include "network_socket.h"
#include <iostream>

using namespace std;

bool NetworkSocket::socket_write(string msg) {
    if (write(sockfd, (msg + DELIMITER).c_str(), strlen(msg.c_str()) + 1) < 0) {
        return false;
    }
    return true;
}


bool NetworkSocket::socket_read(string* msg) {
    char buffer[256];
    bzero(buffer,256); // Clearing buffer before reading into it
    int n = read(sockfd, buffer, 255);
    *msg = buffer;

    // Nothing to be read
    if ((n == -1 && errno == EAGAIN)) {
	    *msg = "";
        return true;

    } else if (n <= 0) { // n == 0 if socket has no connection
	    *msg = "";
        return false;

    }
    return true;
}


void NetworkSocket::interpret_message(string msg_read) {
    string word;
    istringstream iss(msg_read);

    while (getline(iss, word, DELIMITER)) {
        // Writes each message to queue 2, from socket to a module
        thread_com->write_to_queue(word, 2);
    }
}


bool NetworkSocket::write_read_interpret() {
    string msg_read;
    string msg_write = "";

    //Read from the module and relay this msg with socket_write
    msg_write = thread_com->read_from_queue(1);
    if (msg_write != "") {
        if (socket_write(msg_write) == false) {
            return false;
        }
    }


    if (socket_read(&msg_read) == false) {
        return false;
    }

    if(msg_read != "") {
        interpret_message(msg_read);
    }

    return true;
}
