#include "main_window.h"
#include "ui_main_window.h"
#include <QPixmap>
#include <QFileDialog>

const string COMMAND_ERROR = "ERROR! There was an error executing your command: ";

MainWindow::MainWindow(CommandHandler* handler, StateHandler* state, ClientSocket *com_module, InterThreadCom* thread_com, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setFixedSize(1400,800);
    ui->setupUi(this);
    cmd_handler = handler;
    state_handler = state;
    communication_module = com_module;
    thread_com_module = thread_com;
    state_handler->reset();

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(100);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update(){

    /* update GUI */
    ui->line_sensor_state->setText(QString::fromStdString(state_handler->line_sensor_state));
    ui->line_sensor_value->setText(QString::fromStdString(state_handler->line_sensor_value));
    ui->ware_one_value->setText(QString::fromStdString(state_handler->ware_one_value));
    ui->ware_two_value->setText(QString::fromStdString(state_handler->ware_two_value));
    ui->going_to_label->setText(QString::fromStdString(state_handler->getting_id));
    ui->current_lager_label->setText(QString::fromStdString(state_handler->lager_file));

    if (communication_module->is_connected()){

        if (has_reset){
            cmd_handler->try_command("auto");
            ui->tabWidget->setCurrentIndex(0); // change to auto-mode tab
            has_reset = false;
        }

        cmd_handler->try_command("getsensors");

        if (ui->tabWidget->currentIndex() == 0) {

            cmd_handler->try_command("getroute");

            string route = state_handler->route;
            string getting_id;

            if ( route.length() < 3 ){
                getting_id = route.substr(0, 1);
            }
            else {
                //will not write the hundreds if node id is over 99
                getting_id = route.substr(route.length()- 3, 2);
            }

            if (getting_id == "0") { getting_id = "-"; }
            else if (stoi(getting_id) == state_handler->home_id) { getting_id = "Home"; }

            ui->going_to_label->setText(QString::fromStdString(getting_id));
        }
        else {
            ui->going_to_label->setText(QString::fromStdString("Manual controls"));
        }

        ui->is_connected_label->setText(QString::fromStdString("YES"));

        /*  NOTE: "none" can be changed in state-handler */
        if(state_handler->lager_file != state_handler->NO_VALUE_STRING){
            ui->scroll_area->show(); //show lager map
        }
    }
    else {
        has_reset = true;
        state_handler->reset();
        ui->is_connected_label->setText(QString::fromStdString("NO"));
        ui->scroll_area->hide(); //hide lager map

        // Read and removes all messages buffered to send to socket
        while(thread_com_module->read_from_queue(TO_SOCKET) != "") {}
    }
}

/*
    Adds a new line and the string msg to string terminal_history and then writes
    terminal_history to the terminal window widget

    string msg - the text that will be written to the terminal window widget
*/
void MainWindow::write_to_terminal_window(string msg){
    string tmp = terminal_history.QString::toStdString() + "\n" + msg;
    terminal_history = QString::fromStdString(tmp);
    ui->terminal_window->setText(terminal_history);
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

    bool cmd_accepted = cmd_handler->try_command(command);

    string write_terminal = "> " + command;
    write_to_terminal_window(write_terminal);

    if(!cmd_accepted){
        string error_msg = COMMAND_ERROR + command;
        write_to_terminal_window(error_msg);
    }


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
        ui->current_lager_label->setText(QString::fromStdString(state_handler->lager_file));
    }
    else {
        string error_msg = COMMAND_ERROR + "No connection to Robot";
        write_to_terminal_window(error_msg);
    }

}

/*
    Read what id the user has entered in the get-ware-box and sends the command to the command handler.
    Also updates state_handler.
    If command failed it prints an error message to the GUI terminal window.
*/
void MainWindow::on_go_get_ware_button_clicked()
{
    string get_command = "get ";
    string id = ui->get_id_spin_box->text().toStdString();
    get_command = get_command + id;
    bool cmd_accepted = cmd_handler->try_command(get_command);

    if(!cmd_accepted){
        string error_msg = COMMAND_ERROR + get_command;
        write_to_terminal_window(error_msg);
    }
    else {
        state_handler->getting_id = id;
        write_to_terminal_window("Robot will get the ware at " + id + " for you!");

    }
}

/*
    When read_lager_file_button has ben clicked it will open a file dialog where user can
    select lager file. The lager file will then be sent to the command handler. If successful
    it will also try to read an image of the lager and display it, else it will write an
    error message to the GUI terminal window.
*/
void MainWindow::on_read_lager_file_button_clicked()
{
    if(communication_module->is_connected()){
        string file = QFileDialog::getOpenFileName(this, tr("Open File"), "~/").toStdString();
        string lager_command = "lager " + file;

        bool cmd_accepted = cmd_handler->try_command(lager_command);

        if (!cmd_accepted){
            string error_msg = COMMAND_ERROR + lager_command;
            write_to_terminal_window(error_msg);
        }
        else {
            state_handler->lager_file = file;
            QPixmap lager(QString::fromStdString(file+".png"));
            QLabel *label = new QLabel();
            ui->scroll_area->setWidget(label);
            label->setPixmap(lager);
            ui->scroll_area->hide();
        }
    }else{
        write_to_terminal_window("can't read lager when disconnected");
    }
}

void MainWindow::on_set_home_button_clicked()
{
    string home_id = ui->set_home_box->text().toStdString();
    string cmd = "sethome " + home_id;
    bool cmd_accepted = cmd_handler->try_command(cmd);

    if(!cmd_accepted){
        string error_msg = COMMAND_ERROR + cmd;
        write_to_terminal_window(error_msg);
    }
    else {
        write_to_terminal_window(("Home set to " + home_id + "!"));
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

void MainWindow::on_cal_ware_sensors_clicked()
{
    if (communication_module->is_connected()){
        cmd_handler->try_command("calware");
        write_to_terminal_window("Ware sensors calibrated!");
    }
    else {
        write_to_terminal_window("Could not calibrate. Not connected.");
    }
}

void MainWindow::on_cal_line_sensors_line_clicked()
{
    if (communication_module->is_connected()){
        cmd_handler->try_command("calline");
        write_to_terminal_window("Line sensors calibrated for line!");
    }
    else {
        write_to_terminal_window("Could not calibrate. Not connected.");
    }
}

void MainWindow::on_cal_line_sensors_floor_clicked()
{
    if (communication_module->is_connected()){
        cmd_handler->try_command("calfloor");
        write_to_terminal_window("Line sensors calibrated for floor!");
    }
    else {
        write_to_terminal_window("Could not calibrate. Not connected.");
    }
}

void MainWindow::on_arm_home_button_clicked()
{
    cmd_handler->try_command("armhome");
}

void MainWindow::on_set_drive_turn_speed_clicked()
{
    string drive_speed = ui->drive_speed_value->text().toStdString();
    string turn_speed = ui->turn_speed_value->text().toStdString();
    string set_drive_speed = "drivespeed " + drive_speed;
    string set_turn_speed = "turnspeed " + turn_speed;
    cmd_handler->try_command(set_drive_speed);
    cmd_handler->try_command(set_turn_speed);

    string print = "Drive speed set to " + drive_speed + ", turn speed set to " + turn_speed;
    write_to_terminal_window(print);
}
