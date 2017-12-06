#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <iostream>
#include "../command_handler.h"
#include "../client_socket.h"
#include "state_handler.h"

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

    void on_tabWidget_tabBarClicked(int index);

    void on_fwd_button_pressed();

    void on_fwd_button_released();

    void on_left_button_pressed();

    void on_left_button_released();

    void on_back_button_pressed();

    void on_back_button_released();

    void on_right_button_pressed();

    void on_right_button_released();

    void on_find_ware_button_clicked();

    void on_pick_up_button_clicked();

    void on_put_down_button_clicked();

    void on_open_claw_button_clicked();

    void on_close_claw_button_clicked();

    void on_arm_up_button_pressed();

    void on_arm_up_button_released();

    void on_arm_down_button_pressed();

    void on_arm_down_button_released();

    void on_arm_back_button_pressed();

    void on_arm_back_button_released();

    void on_arm_fwd_button_pressed();

    void on_arm_fwd_button_released();

    void on_emergency_stop_button_pressed();

private:
    CommandHandler* cmd_handler;
    Ui::MainWindow *ui;
};

#endif // MAIN_WINDOW_H
