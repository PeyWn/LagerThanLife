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
    CommandHandler cmd_handler(thread_com, &state_handler);

    // Create a new thread to handle communication
    com_module = new ClientSocket(thread_com); //programmet startar inte om inte detta lyckas. ??
    //cout << "Connected!" << endl;

    thread com_child([](){com_module->main_loop();});


    QApplication a(argc, argv);
    MainWindow w(&cmd_handler, &state_handler, com_module);
    w.show();

    return a.exec();

}
