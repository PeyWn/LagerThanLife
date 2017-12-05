#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include "../command_handler.h"
#include "../client_socket.h"
#include <iostream>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(CommandHandler* handler, QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_5_pressed();

    void on_pushButton_5_released();

    void on_pushButton_18_pressed();

    void on_pushButton_18_released();

    void on_tabWidget_tabBarClicked(int index);

private:
    CommandHandler* cmd_handler;
    Ui::MainWindow *ui;
};

#endif // MAIN_WINDOW_H
