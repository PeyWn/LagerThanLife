#include "interthreadcom.h"

InterThreadCom::InterThreadCom() {}

void InterThreadCom::write_to_queue(string msg, int queue) {
    if (queue == 1) {
        mtx_queue1.lock();
        queue1.push(msg);
        mtx_queue1.unlock();
    }

    else if (queue == 2) {
        mtx_queue2.lock();
        queue2.push(msg);
        mtx_queue2.unlock();
    }
}

string InterThreadCom::read_from_queue(int queue) {
    string msg = "";

    if (queue == 1) {
        mtx_queue1.lock();
        
        if(!queue1.empty()) {
            msg = queue1.front();
            queue1.pop();
        }

        mtx_queue1.unlock();
    }

    else if (queue == 2) {
        mtx_queue2.lock();

        if(!queue2.empty()) {
            msg = queue2.front();
            queue2.pop();
        }

        mtx_queue2.unlock();
    }

    return msg;
}