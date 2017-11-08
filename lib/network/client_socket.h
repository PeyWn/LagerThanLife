/**
    Implementation of clientside of socket communication
*/

#ifndef CLIENT_SOCKET_H
#define CLIENT_SOCKET_H

#include <unistd.h>
#include <netdb.h>
#include "interthreadcom.h"
#include "network_socket.h"

using namespace std;

class ClientSocket: public NetworkSocket {
public:
    ClientSocket(InterThreadCom* inter_thread_com);

    bool new_connection();

    void main_loop();
private:
    const string disconnect_msg = "Disconnected";
    const string connected_msg = "Connected";
};

#endif // CLIENT_SOCKETS_H
