#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "registered_user.h"
#include "administrators.h"
#include "post.h"
#include "comment.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Registered_user *register_user = new Registered_user;
    Administrators *administrators = new Administrators;

    if(id < 5)
    {
        administrators->info.id = id;
        administrators->info.username = username;
        administrators->info.password = password;
    }
    else
    {
        register_user->info.id = id;
        register_user->info.username = username;
        register_user->info.password = password;
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    per_info = new Personal_infomation(this);
    per_info->username = username;
    per_info->password = password;
    per_info->id = id;
    per_info->show_infomation();
    per_info->setModal(true);
    per_info->show();
}
