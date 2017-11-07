#include <map>
#include "../lib/network/interthreadcom.h"

using namespace std;

class CommandHandler{
private:
    InterThreadCom* robot_com;

    /*
    First is name of command; second (booleans) is if command
    requires parameters after the command itself.
    */
    const map<string, bool> acc_cmd = {
        {"fwd", false},
        {"stop", false},
        {"right", false},
        {"left", false},
        {"noturn", false},
        {"armright", false},
        {"armleft", false},
        {"armstop", false},
        {"pickup", false},
        {"putdown", false},
        {"get", true},
        {"getsensors", false},
        {"getpos", false},
        {"getroute", false},
        {"updateall", false},
        {"auto", false},
        {"manual", false},
        {"armfwd", false},
        {"armback", false},
        {"armup", false},
        {"armdown", false},
        {"closegrap", false},
        {"closegrap", false},
        {"opengrap", false},
        {"rotgrip", false},
        {"stop", false},
        {"fwd", false},
        {"lager", true},
        {"sethome", true}
    };

    void send_msg(string msg);
public:
    CommandHandler(InterThreadCom* com);
    bool try_command(string cmd);
};
