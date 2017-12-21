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

    // Create a new thread to handle communication
    com_module = new ClientSocket(thread_com);

    CommandHandler cmd_handler(thread_com, &state_handler, com_module);

    thread com_child([](){com_module->main_loop();});

    QApplication a(argc, argv);
    MainWindow w(&cmd_handler, &state_handler, com_module, thread_com);
    w.show();

    int exit_value = a.exec();

    com_module->set_stop();
    com_child.join();

    cout << "Exiting" << endl;
    return exit_value;

}
