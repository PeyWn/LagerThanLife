#include "main_window.h"
#include <QApplication>
#include <thread>
#include <iostream>

#include <signal.h>
//#include "../command_handler.h"

InterThreadCom* thread_com;
ClientSocket* com_module;

int main(int argc, char *argv[])
{

    thread_com = new InterThreadCom();
    CommandHandler cmd_handler(thread_com);

    // Create a new thread to handle communication
    //com_module = new ClientSocket(thread_com);

    //thread com_child(comm_mod_loop);
    //thread com_child([](){com_module->main_loop();});

    QApplication a(argc, argv);
    MainWindow w(&cmd_handler);
    w.show();

    return a.exec();
}
