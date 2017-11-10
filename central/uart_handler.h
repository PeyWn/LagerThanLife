using namespace std;

typedef char uart_msg;

class UARTHandler{
private:
    int uart_fd;
public:
    UARTHandler(string interface);
    void send_msg(int msg);
    bool read_msg(uart_msg buffer[]);
};
