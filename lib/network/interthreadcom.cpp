#include "interthreadcom.h"

using namespace std;

InterThreadCom::InterThreadCom() {}

queue<string>* InterThreadCom::get_queue(QUEUE_DIRECTION qd){
    if(qd == TO_SOCKET){
        return &queue_to_socket;
    } else {
        return &queue_from_socket;
    }
}

mutex* InterThreadCom::get_mutex(QUEUE_DIRECTION qd) {
    if(qd == TO_SOCKET) {
        return &mtx_to_socket;
    } else {
        return &mtx_from_socket;
    }
}

void InterThreadCom::write_to_queue(string msg, QUEUE_DIRECTION direction) {
    queue<string>* q = get_queue(direction);
    mutex* mtx = get_mutex(direction);

    mtx->lock();
    q->push(msg);
    mtx->unlock();
}

string InterThreadCom::read_from_queue(QUEUE_DIRECTION direction) {
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
