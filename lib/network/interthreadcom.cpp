#include "interthreadcom.h"

using namespace std;

InterThreadCom::InterThreadCom() {}

void InterThreadCom::write_to_queue(string msg, QueueDirection direction) {
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
