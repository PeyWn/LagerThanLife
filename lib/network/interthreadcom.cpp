#include "interthreadcom.h"
#include <iostream>

using namespace std;

InterThreadCom::InterThreadCom() {}

queue<string>* InterThreadCom::get_queue(QueueDirection qd){
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
    queue<string>* q = get_queue(direction);
    mutex* mtx = get_mutex(direction);

    mtx->lock();
    q->push(msg);
    mtx->unlock();
}

string InterThreadCom::read_from_queue(QueueDirection direction) {
    queue<string>* q = get_queue(direction);
    mutex* mtx = get_mutex(direction);
    string msg = "";

    mtx->lock();
    if(!q->empty()) {
        msg = q->front();
        q->pop();
    }
    mtx->unlock();

    return msg;
}
