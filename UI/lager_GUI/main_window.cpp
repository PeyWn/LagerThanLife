#include "main_window.h"
#include "ui_main_window.h"

const string COMMAND_ERROR = "ERROR! There was an error executing your command: ";

MainWindow::MainWindow(CommandHandler* handler, StateHandler* state, ClientSocket *com_module, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cmd_handler = handler;
    state_handler = state;
    communication_module = com_module;

}

MainWindow::~MainWindow()
{
    delete ui;
}

//denna funktion tror jag vi skrotar
void MainWindow::update_variables(string variable, string value){
    if (variable == "ware_one_value"){
        ui->ware_one_value->setText(QString::fromStdString(state_handler->ware_one_value));
    }
    else if (variable == "ware_two_value"){
        ui->ware_two_value->setText(QString::fromStdString(state_handler->ware_two_value));
    }
    else if (variable == "line_sensor_state"){
        ui->line_sensor_state->setText(QString::fromStdString(state_handler->line_sensor_state));
    }
    else if (variable == "line_sensor_value"){
        ui->line_sensor_value->setText(QString::fromStdString(state_handler->line_sensor_value));
    }
    else if (variable == "lager"){
    }
    else if (variable == "drivespeed"){
    }
    else if (variable == "turnspeed"){
    }
    else if (variable == "drive_status"){
    }
    else if (variable == "turn_status"){
    }
    else if (variable == "curr_pos"){
    }
    else if (variable == "route"){
    }

}

void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    if ( index == 0) {
        cmd_handler->try_command("auto");
    }
    else if (index == 1) {
        cmd_handler->try_command("manual");
    }
}

void MainWindow::on_fwd_button_pressed()
{
    //call "fwd"
    cmd_handler->try_command("fwd");
}

void MainWindow::on_fwd_button_released()
{
    //call "stop" (release of fwd button)
    cmd_handler->try_command("stop");
}

void MainWindow::on_left_button_pressed()
{
    //call "left"
    cmd_handler->try_command("left");
}

void MainWindow::on_left_button_released()
{
    //call "stop" (release of left button)
    cmd_handler->try_command("noturn");
}

void MainWindow::on_back_button_pressed()
{
    cmd_handler->try_command("back");
}

void MainWindow::on_back_button_released()
{
    cmd_handler->try_command("stop");
}

void MainWindow::on_right_button_pressed()
{
    cmd_handler->try_command("right");
}

void MainWindow::on_right_button_released()
{
    cmd_handler->try_command("noturn");
}

void MainWindow::on_find_ware_button_clicked()
{
    cmd_handler->try_command("center");
}

void MainWindow::on_pick_up_button_clicked()
{
    cmd_handler->try_command("pickup");
}

void MainWindow::on_put_down_button_clicked()
{
    cmd_handler->try_command("putdown");
}

void MainWindow::on_open_claw_button_clicked()
{
    cmd_handler->try_command("openclaw");
}

void MainWindow::on_close_claw_button_clicked()
{
    cmd_handler->try_command("closeclaw");
}

void MainWindow::on_emergency_stop_button_pressed()
{
    cmd_handler->try_command("estop");
}

void MainWindow::on_terminal_prompt_returnPressed()
{
    command = ui->terminal_prompt->text().toStdString();
    ui->terminal_prompt->clear();

    string tmp = terminal_history.QString::toStdString() + "\n > " + command;

    terminal_history = QString::fromStdString(tmp);

    ui->terminal_window->setText(terminal_history);

    //ui->terminal_window->ensureCursorVisible();

}

void MainWindow::on_update_sensors_button_clicked()
{
    if (communication_module->is_connected())
    {
        cmd_handler->try_command("getsensors");
        ui->line_sensor_state->setText(QString::fromStdString(state_handler->line_sensor_state));
        ui->line_sensor_value->setText(QString::fromStdString(state_handler->line_sensor_value));
        ui->ware_one_value->setText(QString::fromStdString(state_handler->ware_one_value));
        ui->ware_two_value->setText(QString::fromStdString(state_handler->ware_two_value));
    }
    else {
        string tmp = terminal_history.QString::toStdString() + "\n" + COMMAND_ERROR + "No connection to robot";
        terminal_history = QString::fromStdString(tmp);
        ui->terminal_window->setText(terminal_history);
    }

}

void MainWindow::on_go_get_ware_button_clicked()
{
    string get_command = "get ";
    string id = ui->get_id_spin_box->text().toStdString();
    get_command = get_command + id;
    bool cmd_accepted = cmd_handler->try_command(get_command);

    if(!cmd_accepted){
        string tmp = terminal_history.QString::toStdString() + "\n" + COMMAND_ERROR + get_command;
        terminal_history = QString::fromStdString(tmp);
        ui->terminal_window->setText(terminal_history);
    }

}

void MainWindow::on_read_lager_file_button_clicked()
{
    string lager_com = "lager " + ui->lager_file_name->text().toStdString();
    ui->lager_file_name->clear();
    cmd_handler->try_command(lager_com);

    ui->temp_lager_viewer->setText(QString::fromStdString(state_handler->lager));
}

void MainWindow::on_pushButton_clicked()
{
    string set_drive_speed = "drivespeed " + ui->drive_speed_value->text().toStdString();
    string set_turn_speed = "turnspeed " + ui->turn_speed_value->text().toStdString();
    cmd_handler->try_command(set_drive_speed);
    cmd_handler->try_command(set_turn_speed);
}

void MainWindow::on_set_home_button_clicked()
{
    string home_id = ui->set_home_box->text().toStdString();
    string cmd = "sethome " + home_id;
    bool cmd_accepted = cmd_handler->try_command(cmd);

    if(!cmd_accepted){
        string tmp = terminal_history.QString::toStdString() + "\n" + COMMAND_ERROR + cmd;
        terminal_history = QString::fromStdString(tmp);
        ui->terminal_window->setText(terminal_history);
    }

}

void MainWindow::on_arm_2_back_button_pressed()
{
    cmd_handler->try_command("arm2fwd");
}

void MainWindow::on_arm_2_back_button_released()
{
    cmd_handler->try_command("armstop");
}

void MainWindow::on_arm_2_fwd_button_pressed()
{
    cmd_handler->try_command("arm2back");
}

void MainWindow::on_arm_2_fwd_button_released()
{
    cmd_handler->try_command("armstop");
}

void MainWindow::on_arm_1_fwd_button_pressed()
{
    cmd_handler->try_command("arm1fwd");
}

void MainWindow::on_arm_1_fwd_button_released()
{
    cmd_handler->try_command("armstop");
}

void MainWindow::on_arm_1_back_button_pressed()
{
    cmd_handler->try_command("arm1back");
}

void MainWindow::on_arm_1_back_button_released()
{
    cmd_handler->try_command("armstop");
}

void MainWindow::on_arm_3_back_button_pressed()
{
    cmd_handler->try_command("arm3back");
}

void MainWindow::on_arm_3_back_button_released()
{
    cmd_handler->try_command("armstop");
}

void MainWindow::on_arm_3_fwd_button_pressed()
{
    cmd_handler->try_command("arm3fwd");
}

void MainWindow::on_arm_3_fwd_button_released()
{
    cmd_handler->try_command("armstop");
}

void MainWindow::on_arm_ccw_button_pressed()
{
    cmd_handler->try_command("armleft");
}

void MainWindow::on_arm_ccw_button_released()
{
    cmd_handler->try_command("armstop");
}

void MainWindow::on_arm_cw_button_pressed()
{
    cmd_handler->try_command("armright");
}

void MainWindow::on_arm_cw_button_released()
{
    cmd_handler->try_command("armstop");
}

void MainWindow::on_arm_ccw_button_2_clicked()
{
    cmd_handler->try_command("armhome");

}

void MainWindow::on_pushButton_2_clicked()
{
    string is_connected;

    if (communication_module->is_connected()){
        is_connected = "YES";
    }
    else { is_connected = "NO"; }

    ui->is_connected_label->setText(QString::fromStdString(is_connected));
}
