#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <iostream>
#include "../command_handler.h"
#include "../client_socket.h"
#include "state_handler.h"
#include <QTimer>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(CommandHandler* handler, StateHandler *state, ClientSocket* com_module, InterThreadCom* thread_com, QWidget *parent = 0);
    ~MainWindow();


private slots:

    /*
        Function that checks if we have a connection to the robot and if so updates a label
        in the GUI that says it's connected. Also asks for sensor values and prints these
        values to the GUI.
        If there is no connection, it updates the connection-label as well as the sensor values
        telling us that there is no connection.

        update() is called every 0.1 seconds (A timer for this is made in the constructor)
    */
    void update();

    /*
        Function that takes a strign as input, adds it to another string where everything
        we have printed to the "terminal window" is saved. It then prints that string to
        the terminal window simulating a real terminal.

        string msg - what we want to be printed to the terminal
    */
    void write_to_terminal_window(string msg);

    /*
        Function for selecting manual/automatic mode.

        int index - 0 if in "Automatic control" tab, 1 if in "Manual control tab".
        Depending on index 0 or 1, this function sends the command "auto" or "manual"
        to command_handler.
    */
    void on_tabWidget_tabBarClicked(int index);

    /*
        All the 39 functions below are triggered by events and handles different
        actions that the user can do in the GUI. For example on_fwd_button_pressed()
        is called when the user presses the fwd button which sends the command "fwd" to
        command handler. When the user then releases that same button on_fwd_button_released()
        is called which sends the command "stop" to command_handler
    */
    void on_fwd_button_pressed();
    void on_fwd_button_released();
    void on_left_button_pressed();
    void on_left_button_released();
    void on_back_button_pressed();
    void on_back_button_released();
    void on_right_button_pressed();
    void on_right_button_released();
    void on_pick_up_button_clicked();
    void on_put_down_button_clicked();
    void on_open_claw_button_clicked();
    void on_close_claw_button_clicked();
    void on_emergency_stop_button_pressed();
    void on_terminal_prompt_returnPressed();
    void on_update_sensors_button_clicked();
    void on_go_get_ware_button_clicked();
    void on_read_lager_file_button_clicked();
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
    void on_cal_ware_sensors_clicked();
    void on_cal_line_sensors_line_clicked();
    void on_cal_line_sensors_floor_clicked();
    void on_arm_home_button_clicked();
    void on_set_drive_turn_speed_clicked();

private:
    CommandHandler* cmd_handler;
    StateHandler* state_handler;
    ClientSocket* communication_module;
    InterThreadCom* thread_com_module;
    Ui::MainWindow *ui;

    string command; //saves the last command written to the command promt
    QString terminal_history; // saves the terminal history
};

#endif // MAIN_WINDOW_H
