#ifndef INTERTHREADCOM_H
#define INTERTHREADCOM_H

#include <mutex>
#include <queue>
#include <string>

enum QUEUE_DIRECTION{TO_SOCKET, FROM_SOCKET};

/*
    InterThreadCom used for communication between a module and CommunicationModule
    Each queue is a one way communication having each mutex lock.
*/
class InterThreadCom {
private:
    std::mutex mtx_to_socket, mtx_from_socket;
    std::queue<std::string> queue_to_socket, queue_from_socket;
public:
    /*
    Construct a new InterThreadCom object
    */
    InterThreadCom();

    /*
        Gets a pointer to the queue with given queue direction

        qd - queue direction of the queue

        Return - a pointer to the queue
    */
    std::queue<std::string>* get_queue(QUEUE_DIRECTION qd);

    /*
        Gets a pointer to a mutex with given queue direction

        qd - queue direction of the mutex

        Return - a pointer to the mutex
    */
    std::mutex* get_mutex(QUEUE_DIRECTION qd);

    /*
        Writes a message containing a string to a queue.

        msg - Message that is to be pushed to the queue.
        direction - specify writing to socket or from socket
    */
    void write_to_queue(std::string msg, QUEUE_DIRECTION direction);

    /*
        Reads a message and removes it from a queue

        direction - specifying reading to socket or from socket

        Return - a string with the read message, empty string if queue is empty
    */
    std::string read_from_queue(QUEUE_DIRECTION direction);
};
#endif // INTERTHREADCOM_H
