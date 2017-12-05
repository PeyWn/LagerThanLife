#include "main_window.h"
#include "ui_main_window.h"



MainWindow::MainWindow(CommandHandler* handler, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    cmd_handler = handler;

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_5_pressed()
{
    //call "fwd"
    cmd_handler->try_command("fwd");
}

void MainWindow::on_pushButton_5_released()
{
    //call "stop" (release of fwd button)
    cmd_handler->try_command("stop");
}

void MainWindow::on_pushButton_18_pressed()
{
    //call "left"
    cmd_handler->try_command("left");
}

void MainWindow::on_pushButton_18_released()
{
    //call "stop" (release of left button)
    cmd_handler->try_command("noturn");
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

void MainWindow::on_pushButton_8_clicked()
{
    cmd_handler->try_command("pickup");
}

void MainWindow::on_pushButton_19_pressed()
{
    cmd_handler->try_command("back");
}

void MainWindow::on_pushButton_19_released()
{
    cmd_handler->try_command("stop");
}


void MainWindow::on_pushButton_pressed()
{
    cmd_handler->try_command("right");
}

void MainWindow::on_pushButton_released()
{
    cmd_handler->try_command("noturn");
}

void MainWindow::on_pushButton_6_clicked()
{
    cmd_handler->try_command("openclaw");
}

void MainWindow::on_pushButton_7_clicked()
{
    cmd_handler->try_command("closeclaw");
}

void MainWindow::on_pushButton_12_pressed()
{
    cmd_handler->try_command("armup");
}

void MainWindow::on_pushButton_12_released()
{
    cmd_handler->try_command("armstop");
}

void MainWindow::on_pushButton_20_pressed()
{
    cmd_handler->try_command("armdown");
}

void MainWindow::on_pushButton_20_released()
{
    cmd_handler->try_command("armstop");
}

void MainWindow::on_pushButton_21_pressed()
{
    cmd_handler->try_command("armback");
}

void MainWindow::on_pushButton_21_released()
{
    cmd_handler->try_command("armstop");
}

void MainWindow::on_pushButton_3_pressed()
{
    cmd_handler->try_command("armfwd");
}

void MainWindow::on_pushButton_3_released()
{
    cmd_handler->try_command("armstop");
}

void MainWindow::on_pushButton_10_clicked()
{
    cmd_handler->try_command("center");
}

void MainWindow::on_pushButton_9_clicked()
{
    cmd_handler->try_command("putdown");
}

void MainWindow::on_pushButton_2_clicked()
{
    cmd_handler->try_command("estop");
}
