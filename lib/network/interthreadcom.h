/**
    InterThreadCom used for communication between a module and CommunicationModule
    Each queue is a one way communication having each mutex lock.
    Queue 1 is used for communication from a module to socket
    Queue 2 is used for communication from socket to a module
*/

#ifndef INTERTHREADCOM_H
#define INTERTHREADCOM_H

#include <mutex>
#include <queue>
#include "string"

enum QueueDirection {TO_SOCKET, FROM_SOCKET};

class InterThreadCom {

private:
    std::mutex mtx_to_socket, mtx_from_socket;
    std::queue<std::string> queue_to_socket, queue_from_socket;

public:

    InterThreadCom();

    /*
        Writes a message containing a string to a queue.

        string msg - Message that is to be pushed to the queue.
        int queue - specify writing to queue1 or queue2
    */
    void write_to_queue(std::string msg, QueueDirection direction);

    /*
        Reads a message and removes it from a queue

        int queue - speicify reading from queue 1 or queue 2

        Returns a string with the read message
    */
    std::string read_from_queue(QueueDirection direction);

};

#endif // INTERTHREADCOM_H
