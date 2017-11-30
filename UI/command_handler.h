#include <map>
#include "../lib/network/interthreadcom.h"
#include "text_file_handler.h"

using namespace std;

class CommandHandler{
private:
    InterThreadCom* robot_com; //Module to use to send messages to robot
    TextFileHandler text_file_handler;

    /*
    First is name of command; second (booleans) is if command
    requires parameters after the command itself.
    */
    const map<string, bool> acc_cmd = {
        {"fwd", false},
        {"stop", false},
        {"back", false},
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
        {"closeclaw", false},
        {"openclaw", false},
        {"opengclaw", false},
        {"estop", false},
        {"lager", true},
        {"sethome", true},
        {"calware", false},
        {"calline", false},
        {"calfloor", false},
        {"armhome", false},
        {"turnspeed", true},
        {"drivespeed", true},
        {"showdata", false},
        {"center", false}
    };

    /*
    Send a message to the robot using robot_com

    msg - the string to be sent
    */
    void send_msg(string msg);
public:
    /*
    Construct a CommandHandler Objext

    com - pointer to InterThreadCom module to use to send messages to robot
    */
    CommandHandler(InterThreadCom* com);

    /*
    try to execute given string as a command. Return if it worked

    cmd - the string as a command to try to use (example "stop", "get 3")

    return - if the command could be executed succesfully
    */
    bool try_command(string cmd);
};
