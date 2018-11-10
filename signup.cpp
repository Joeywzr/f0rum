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
    {
        qDebug() << "username is empty!";
        return;
    }
    else
    {
        QString select_sql = "select username from registered_user";
        if(!sql_query.exec(select_sql))
            qDebug()<<sql_query.lastError();
        else
        {
            while(sql_query.next())
            {
                QString username = sql_query.value(0).toString();
                if(username_input == username)
                {
                    qDebug()<<"The username has been occupied.";
                    return;
                }
            }
        }
    }
    if(password_input.isEmpty())
    {
        qDebug() << "password is empty!";
        return;
    }
    if(confirm_password_input.isEmpty())
    {
        qDebug() << "confirm_password is empty!";
        return;
    }
    if(confirm_password_input != password_input)
    {
        qDebug() << "The passwords entered two times are different.";
        return;
    }

    QString insert_sql = "insert into registered_user values (?, ?, ?)";
    sql_query.prepare(insert_sql);
    sql_query.addBindValue(max_id);
    sql_query.addBindValue(username_input);
    sql_query.addBindValue(password_input);
    if(!sql_query.exec())
    {
        qDebug() << sql_query.lastError();
    }
    else
    {
        qDebug() << "inserted " << username_input << "!";
        max_id++;
        qDebug() << "max id ="<<max_id;
    }
    this->close();
}
