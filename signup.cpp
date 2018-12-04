#include "signup.h"
#include "ui_signup.h"


signup::signup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::signup)
{
    ui->setupUi(this);
    this->setWindowTitle(QObject::tr("注册"));
    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." << database.lastError();
    }
}

signup::~signup()
{
    delete ui;
}

void signup::on_signup_2_clicked()//点击注册按钮
{
    QString username_input = ui->username->text(),
            password_input = ui->password->text(),
            confirm_password_input = ui->confirm_password->text();
    if(username_input.isEmpty())
    {
        ui->warning->setText("用户名不能为空！");
        ui->username->clear();
        ui->password->clear();
        ui->confirm_password->clear();
        qDebug() << "username is empty!";
        return;
    }
    else
    {
        QString select_sql = "select username from users";
        if(!sql_query.exec(select_sql))
            qDebug()<<sql_query.lastError();
        else
        {
            while(sql_query.next())
            {
                QString username = sql_query.value(0).toString();
                if(username_input == username)
                {
                    ui->warning->setText("用户名已被占用！");
                    ui->username->clear();
                    ui->password->clear();
                    ui->confirm_password->clear();
                    qDebug()<<"The username has been occupied.";
                    return;
                }
            }
        }
    }
    if(password_input.isEmpty())
    {
        ui->warning->setText("密码不能为空！");
        ui->username->clear();
        ui->password->clear();
        ui->confirm_password->clear();
        qDebug() << "password is empty!";
        return;
    }
    if(confirm_password_input.isEmpty())
    {
        ui->warning->setText("确认密码不能为空！");
        ui->username->clear();
        ui->password->clear();
        ui->confirm_password->clear();
        qDebug() << "confirm_password is empty!";
        return;
    }
    if(confirm_password_input != password_input)
    {
        ui->warning->setText("两次输入的密码不一致！");
        ui->username->clear();
        ui->password->clear();
        ui->confirm_password->clear();
        qDebug() << "The passwords entered two times are different.";
        return;
    }

    QString insert_sql = "insert into users values (?, ?, ?, ?, ?)";
    sql_query.prepare(insert_sql);
    sql_query.addBindValue(max_id);
    sql_query.addBindValue(username_input);
    sql_query.addBindValue(password_input);
    if(max_id>5)
        sql_query.addBindValue("ordinary");
    else
        sql_query.addBindValue("administrator");
    sql_query.addBindValue(0);

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
