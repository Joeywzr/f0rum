#include "signup.h"
#include "ui_signup.h"


signup::signup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::signup)
{
    ui->setupUi(this);
    this->setWindowTitle(QObject::tr("注册"));
    QRegExp rx("[^\\s]+$");
    QRegExpValidator *validator = new QRegExpValidator(rx, this);
    ui->username->setValidator(validator);
    ui->password->setValidator(validator);
    ui->confirm_password->setValidator(validator);
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
        for(int i = 0;i < all_users.size();i++)
        {
            QString username = all_users[i].username;
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
    max_id = all_users.last().id + 1;
    qDebug() << all_users.last().username;
    user_variable uu;
    uu.id = max_id;
    uu.username = username_input;
    uu.password = password_input;
    if(max_id>5)
        uu.level = "ordinary";
    else
        uu.level = "administrator";
    uu.responsible_plate = 0;
    all_users.push_back(uu);
    qDebug() << "inserted " << username_input << "!";
    this->close();
}
