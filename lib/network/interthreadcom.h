/**
    InterThreadCom used for communication between a module and CommunicationModule
    Each queue is a one way communication having each mutex lock.
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
        Gets a queue with given queue direction

        qd - queue direction of the queue

        Returns a pointer to the queue
    */
    queue* get_queue(QueueDirection qd);

    /*
        Gets a mutex with given queue direction

        qd - queue direction of the mutex

        Returns a pointer to the mutex
    */
    mutex* get_mutex(QueueDirection qd);

    /*
        Writes a message containing a string to a queue.

        string msg - Message that is to be pushed to the queue.
        direction - specify writing to socket or from socket
    */
    void write_to_queue(std::string msg, QueueDirection direction);

    /*
        Reads a message and removes it from a queue

        direction - specifying reading to socket or from socket

        Returns a string with the read message
    */
    std::string read_from_queue(QueueDirection direction);

};

#endif // INTERTHREADCOM_H
