using namespace std;

class UARTHandler{
private:
public:
    UARTHandler(string interface);
    void send_msg(int msg);
    int read_msg();
}
