#include "signup.h"
#include "ui_signup.h"


signup::signup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::signup)
{
    ui->setupUi(this);
    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." << database.lastError();
    }
    else
    {
        QSqlQuery sql_query;
        QString select_sql = "select id, name from registered_user";
        if(!sql_query.exec(select_sql))
        {
            QString create_sql = "create table registered_user (id int , username QString, password QString)";
            sql_query.prepare(create_sql);
            if(!sql_query.exec())
            {
                qDebug() << "Error: Fail to create table." << sql_query.lastError();
            }
            else
            {
                qDebug() << "Table created!";
            }
        }
    }


}

signup::~signup()
{
    delete ui;
}

void signup::on_signup_2_clicked()
{
    QString username_input = ui->username->text(),
            password_input = ui->password->text(),
            confirm_password_input = ui->confirm_password->text();
    if(username_input.isEmpty())
        qDebug() << "username is empty!";
    else if(password_input.isEmpty())
        qDebug() << "password is empty!";
    else if(confirm_password_input.isEmpty())
        qDebug() << "confirm_password is empty!";
    else if(confirm_password_input != password_input)
        qDebug() << "The passwords entered two times are different.";
}
