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
}

void MainWindow::on_pushButton_18_released()
{
    //call "stop" (release of left button) -- How do I make this the same as on_pushButton_5_released(),
    //                                          make it one function (else there will be 100 of thee )
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
