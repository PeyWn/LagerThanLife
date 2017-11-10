using namespace std;

typedef char uart_msg;

class UARTHandler{
private:
    int uart_fd;
public:
    UARTHandler(string interface);
    void send_msg(int msg);
    int read_msg();
};
