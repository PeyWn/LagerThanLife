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
    bool connected;
    
    ClientSocket(InterThreadCom* inter_thread_com);

    /*
        Starts a new socket connection to the server
    */
    bool new_connection();

    /*
        Main loop for server_socket. Read, writes and interpret
        messages using function write_read_interpret. Sets
        connected to false if this fails.
    */
    void main_loop();
    
private:
    const string disconnect_msg = "Disconnected!";
    const string connected_msg = "Connected!";
};

#endif // CLIENT_SOCKETS_H
