#include <cstring>
#include <sstream>
#include <netdb.h>
#include <unistd.h>
#include "network_socket.h"
#include <iostream>

using namespace std;

int NetworkSocket::socket_write(string msg) {
    if (write(sockfd, (msg + DELIMITER).c_str(), strlen(msg.c_str()) + 1) < 0) {
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

    } else if (n < 0) {
        return "-1";

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


int NetworkSocket::write_read_interpret() {
    string msg_read = "";
    string msg_write = "";

    //Read from queue 1 (from a module) and relay this info with socket_write
    msg_write = thread_com->read_from_queue(1);

    if (msg_write != "") {
        if (socket_write(msg_write) < 0) {
            cout << "ERROR1" << endl;
            return -1;
        }
    }

    msg_read = socket_read();

    if (msg_read != "") {
        if (msg_read == "-1") {
            //thread_com->write_to_queue(msg_write, 1);   //Readd message to the module
            
            cout << "ERROR2" << endl;
            return -1;
        }
        interpret_message(msg_read);
    }

    return 0;
}
