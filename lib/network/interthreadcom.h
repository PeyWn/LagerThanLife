/**
    InterThreadCom used for communication between CentralModule and CommunicationModule
    Each queue is a one way communication having each mutex lock.
    Queue 1 is used for communication from a module to socket
    Queue 2 is used for communication from socket to a module
*/

#ifndef INTERTHREADCOM_H
#define INTERTHREADCOM_H

#include <mutex>
#include "string"
#include <queue>

class InterThreadCom {

private:
    std::mutex mtx_queue1, mtx_queue2;
    std::queue<std::string> queue1, queue2;

public:
    InterThreadCom();

    /*
        Writes a message containing a string to a queue.

        string msg - Message that is to be pushed to the queue.
        int queue - specify writing to queue1 or queue2
    */
    void write_to_queue(std::string msg, int queue);

    /*
        Reads a message and removes it from a queue

        int queue - speicify reading from queue1 or queue2

        Returns a string with the read message
    */
    std::string read_from_queue(int queue);

};

#endif // INTERTHREADCOM_H
