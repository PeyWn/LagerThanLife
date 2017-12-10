#include "main_window.h"
#include "ui_main_window.h"



MainWindow::MainWindow(CommandHandler* handler, StateHandler state, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    cmd_handler = handler;
    state_handler = state;

}

MainWindow::~MainWindow()
{
    delete ui;
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

void MainWindow::on_arm_up_button_pressed()
{
    cmd_handler->try_command("armup");
}

void MainWindow::on_arm_up_button_released()
{
    cmd_handler->try_command("armstop");
}

void MainWindow::on_arm_down_button_pressed()
{
    cmd_handler->try_command("armdown");
}

void MainWindow::on_arm_down_button_released()
{
    cmd_handler->try_command("armstop");
}

void MainWindow::on_arm_back_button_pressed()
{
    cmd_handler->try_command("armback");
}

void MainWindow::on_arm_back_button_released()
{
    cmd_handler->try_command("armstop");
}

void MainWindow::on_arm_fwd_button_pressed()
{
    cmd_handler->try_command("armfwd");
}

void MainWindow::on_arm_fwd_button_released()
{
    cmd_handler->try_command("armstop");
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

}


void MainWindow::on_terminal_window_textChanged()
{
    //make it scroll down to the bottom
}

void MainWindow::on_update_sensors_button_clicked()
{
    cmd_handler->try_command("getsensors");
    ui->line_sensor_state->setText(QString::fromStdString(state_handler.line_sensor_state));
    ui->line_sensor_value->setText(QString::fromStdString(state_handler.line_sensor_value));
    ui->ware_one_value->setText(QString::fromStdString(state_handler.ware_one_value));
    ui->ware_two_value->setText(QString::fromStdString(state_handler.ware_two_value));

}

void MainWindow::on_go_get_ware_button_clicked()
{
    string get_command = "get ";
    string id = ui->get_id_spin_box->text().toStdString();
    get_command = get_command + id;
    cmd_handler->try_command(get_command);

}

void MainWindow::on_read_lager_file_button_clicked()
{

    //OBS text_file_handler verkar inte kunna hitta filen???

    string lager_com = "lager " + ui->lager_file_name->text().toStdString();
    ui->lager_file_name->clear();
    cmd_handler->try_command(lager_com);
    ui->temp_lager_viewer->setText(QString::fromStdString(state_handler.lager));
}
