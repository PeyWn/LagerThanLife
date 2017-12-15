/**
    Implementation of clientside of socket communication
*/

#ifndef CLIENT_SOCKET_H
#define CLIENT_SOCKET_H

#include <unistd.h>
#include <netdb.h>
#include "../lib/network/interthreadcom.h"
#include "../lib/network/network_socket.h"

using namespace std;

class ClientSocket: public NetworkSocket {
public:
    ClientSocket(InterThreadCom* inter_thread_com);

    /*
        Getter for variable connected
    */
    bool is_connected();

    /*
        Main loop for server_socket. Read, writes and interpret
        messages using function write_read_interpret. Sets
        variable connected to false if this fails. Main loop will
        stop running if bool stop is has been set.
    */
    void main_loop();

    /*
     * Setter for bool stop
     */
    void set_stop();
    
private:
    bool connected = false;
    bool stop = false;

    const string disconnect_msg = "Disconnected!";
    const string connected_msg = "Connected!";

    /*
        Starts a new socket connection to the server
        
        Returns true if success, else false
    */
    bool new_connection();


};

#endif // CLIENT_SOCKETS_H
