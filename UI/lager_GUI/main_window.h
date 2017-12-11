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
    explicit MainWindow(CommandHandler* handler, StateHandler *state, ClientSocket* com_module, QWidget *parent = 0);
    ~MainWindow();

    void update_variables(string variable, string value);

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

    void on_emergency_stop_button_pressed();

    void on_terminal_prompt_returnPressed();

    void on_update_sensors_button_clicked();

    void on_go_get_ware_button_clicked();

    void on_read_lager_file_button_clicked();

    void on_pushButton_clicked();

    void on_set_home_button_clicked();

    void on_arm_2_back_button_pressed();

    void on_arm_2_back_button_released();

    void on_arm_2_fwd_button_pressed();

    void on_arm_2_fwd_button_released();

    void on_arm_1_fwd_button_pressed();

    void on_arm_1_fwd_button_released();

    void on_arm_1_back_button_pressed();

    void on_arm_1_back_button_released();

    void on_arm_3_back_button_pressed();

    void on_arm_3_back_button_released();

    void on_arm_3_fwd_button_pressed();

    void on_arm_3_fwd_button_released();

    void on_arm_ccw_button_pressed();

    void on_arm_ccw_button_released();

    void on_arm_cw_button_pressed();

    void on_arm_cw_button_released();

    void on_arm_ccw_button_2_clicked();


    void on_pushButton_2_clicked();

private:
    CommandHandler* cmd_handler;
    StateHandler* state_handler;
    ClientSocket* communication_module;
    Ui::MainWindow *ui;

    string command; //saves the last command written to the command promt
    QString terminal_history; // saves the terminal history
};

#endif // MAIN_WINDOW_H
