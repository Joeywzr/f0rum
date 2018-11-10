#include "loginwindow.h"
#include "ui_loginwindow.h"


LoginWindow::LoginWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database.Please reboot the system and try again." << database.lastError();
    }


}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void click_sign_in()
{

}
void LoginWindow::on_sign_in_clicked()
{

}

void LoginWindow::on_sign_up_clicked()
{
    view = new signup(this);
    view->setModal(true);
    view->show();

}
