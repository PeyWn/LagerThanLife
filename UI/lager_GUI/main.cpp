#include <QApplication>
#include <thread>
#include <iostream>
#include <signal.h>
#include "main_window.h"
//#include "../command_handler.h"

InterThreadCom* thread_com;
ClientSocket* com_module;
StateHandler state_handler;

int main(int argc, char *argv[])
{

    cout << "Trying to connect to robot..." << endl;
    thread_com = new InterThreadCom();
    CommandHandler cmd_handler(thread_com, state_handler);

    // Create a new thread to handle communication
    //com_module = new ClientSocket(thread_com);

    //thread com_child(comm_mod_loop); <--- keep commented. What is this?
    //thread com_child([](){com_module->main_loop();});
    //cout << "Connected!" << endl;


    QApplication a(argc, argv);
    MainWindow w(&cmd_handler, state_handler);
    w.show();

    return a.exec();
}
