#include "loginwindow.h"
#include "ui_loginwindow.h"


LoginWindow::LoginWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." << database.lastError();
    }


}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_sign_in_clicked()
{
    QString username_input = ui->username->text(),
            password_input = ui->password->text();
    bool username_flag = false;
    if(username_input.isEmpty())
    {
        qDebug() << "Please input username!";
        return;
    }
    else
    {
        QString select_sql = "select username,password from registered_user";
        if(!sql_query.exec(select_sql))
            qDebug()<<sql_query.lastError();
        else
        {
            while(sql_query.next())
            {
                QString username = sql_query.value(0).toString();
                QString password = sql_query.value(1).toString();
                if(username_input == username)
                {
                    username_flag = true;
                    if(password_input == password)
                    {
                        this->close();
                        mainview = new MainWindow(this);
                        mainview->show();
                    }
                    else
                    {
                        if(password_input.isEmpty())
                        {
                            qDebug() << "password is empty!";
                            return;
                        }
                        else
                        {
                            qDebug() << "Password is wrong.Please try again.";
                            ui->password->setText(NULL);
                            return;
                        }

                    }
                }
            }
            if(username_flag == false)
            {
                ui->username->setText(NULL);
                ui->password->setText(NULL);
                qDebug() << "Username doesn't exist!";
                return;

            }
        }
    }


}

void LoginWindow::on_sign_up_clicked()
{
    view = new signup(this);
    view->setModal(true);
    view->show();

}
