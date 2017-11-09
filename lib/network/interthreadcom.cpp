#include "interthreadcom.h"

using namespace std;

InterThreadCom::InterThreadCom() {}

queue* InterThreadCom::get_queue(QueueDirection qd){
    if(qd == TO_SOCKET){
        return &queue_to_socket;
    } else {
        return &queue_from_socket;
    }
}


mutex* InterThreadCom::get_mutex(QueueDirection qd) {
    if(qd == TO_SOCKET) {
        return &mtx_to_socket;
    } else {
        return &mtx_from_socket;
    }
}


void InterThreadCom::write_to_queue(string msg, QueueDirection direction) {
    queue* q = getQueue(direction);
    mutex* mtx = getMutex(direction);

    mtx->lock();
    q.push(msg);
    mtx->unlock();
}

string InterThreadCom::read_from_queue(QueueDirection direction) {
    queue* q = getQueue(direction);
    mutex* mtx = getMutex(direction);
    string msg = "";

    mtx->lock();
    if(!q->empty()) {
        msg = q->front();
        q->pop();
    }

    return msg;
}

/*void InterThreadCom::write_to_queue(string msg, QueueDirection direction) {
    if (direction == TO_SOCKET) {
        mtx_to_socket.lock();
        queue_to_socket.push(msg);
        mtx_to_socket.unlock();
    }

    else if (direction == FROM_SOCKET) {
        mtx_from_socket.lock();
        queue_from_socket.push(msg);
        mtx_from_socket.unlock();
    }
}

string InterThreadCom::read_from_queue(QueueDirection direction) {
    string msg = "";

    if (direction == TO_SOCKET) {
        mtx_to_socket.lock();
        
        if(!queue_to_socket.empty()) {
            msg = queue_to_socket.front();
            queue_to_socket.pop();
        }

        mtx_to_socket.unlock();
    }

    else if (direction == FROM_SOCKET) {
        mtx_from_socket.lock();

        if(!queue_from_socket.empty()) {
            msg = queue_from_socket.front();
            queue_from_socket.pop();
        }

        mtx_from_socket.unlock();
    }

    return msg;
}
*/