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

    void on_pushButton_8_clicked();

    void on_pushButton_19_pressed();

    void on_pushButton_19_released();

    void on_pushButton_released();

    void on_pushButton_pressed();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_12_pressed();

    void on_pushButton_12_released();

    void on_pushButton_20_pressed();

    void on_pushButton_20_released();

    void on_pushButton_21_pressed();

    void on_pushButton_21_released();

    void on_pushButton_3_pressed();

    void on_pushButton_3_released();

    void on_pushButton_10_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_2_clicked();

private:
    CommandHandler* cmd_handler;
    Ui::MainWindow *ui;
};

#endif // MAIN_WINDOW_H
