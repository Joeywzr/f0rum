#include "loginwindow.h"
#include "ui_loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    ui->sign_in->setFocus();
    this->setWindowTitle(QObject::tr("登录"));

    tcpsocket = new QTcpSocket(this);
    this->connect(ui->to_connect,SIGNAL(clicked(bool)),this,SLOT(connect_sever()));
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_sign_in_clicked()//点击登录按钮
{
    if(!tcpsocket->isOpen())
    {
        ui->warning->setText("未连接服务器！");
        return;
    }
    QString username_input = ui->username->text();
    QString password_input = ui->password->text();
    if(username_input.isEmpty())
    {
        ui->warning->setText("请输入用户名");
        qDebug() << "Please input username!";
        return;
    }
    else if(password_input.isEmpty())
    {
        ui->warning->setText("请输入密码");
        qDebug() << "Please input password!";
        return;
    }
    else
    {
        QString ss = ui->username->text();
        ss.append(" ");
        tcpsocket->write(ss.toStdString().c_str(),strlen(ss.toStdString().c_str()));
        tcpsocket->write(ui->password->text().toStdString().c_str(),strlen(ui->password->text().toStdString().c_str()));
        qDebug()<<"发送信息";
        //等待返还用户数据
        tcpsocket->waitForReadyRead();

        QByteArray qba = tcpsocket->readAll();
        login_return_list = QVariant(qba).toString().split(" ");
        if(login_return_list.size() == 1)
        {
            if(login_return_list[0] == "UDE")
            {
                ui->username->setText(NULL);
                ui->password->setText(NULL);
                ui->warning->setText("用户名不存在！");
                qDebug() << "Username doesn't exist!";
                return;
            }
            else if(login_return_list[0] == "PIW")
            {
                ui->warning->setText("密码错误！请重试！");
                qDebug() << "Password is wrong.Please try again.";
                ui->password->setText(NULL);
                return;
            }
        }
        else if(login_return_list.size() == 3)
        {
            u = new User;
            QString level = login_return_list[0];
            int responsible_plate = login_return_list[1].toInt();
            int id = login_return_list[2].toInt();
            qDebug()<<level << "  " << responsible_plate << "  " << id;
            this->close();
            u = NULL;
            if(level == "administrator")//管理员登录
            {
                u = new Administrators;
                u->id = id;
                u->username = username_input;
                u->password = password_input;
                u->level = level;
                u->tcpsocket = tcpsocket;
                u->init_class();
                connect(u->mainview->ui->sign_out,SIGNAL(clicked(bool)),this,SLOT(show_loginwindow()));
            }
            else if(level == "ordinary")//普通用户登录
            {
                u = new Ordinary_user;
                u->id = id;
                u->username = username_input;
                u->password = password_input;
                u->level = level;
                u->responsible_plate = responsible_plate;
                u->tcpsocket = tcpsocket;
                u->init_class();
                connect(u->mainview->ui->sign_out,SIGNAL(clicked(bool)),this,SLOT(show_loginwindow()));
            }
            else if(level == "moderator")//版主登录
            {
                u = new Moderator_user;
                u->id = id;
                u->username = username_input;
                u->password = password_input;
                u->level = level;
                u->responsible_plate = responsible_plate;
                u->tcpsocket = tcpsocket;
                u->init_class();
                connect(u->mainview->ui->sign_out,SIGNAL(clicked(bool)),this,SLOT(show_loginwindow()));
            }
        }
    }
}
void LoginWindow::on_sign_up_clicked()//点击注册按钮
{
    if(!tcpsocket->isOpen())
    {
        ui->warning->setText("未连接服务器！");
        return;
    }
    view = new signup(this);
    view->setModal(true);
    view->show();
}

void LoginWindow::show_loginwindow()//显示登录界面
{
    new_mainview = new LoginWindow;
    new_mainview->show();
}

void LoginWindow::on_anonymous_clicked()//点击匿名登录
{
    if(!tcpsocket->isOpen())
    {
        ui->warning->setText("未连接服务器！");
        return;
    }
    u = new Anonymous;
    u->id = -1;
    u->init_class();
    connect(u->mainview->ui->sign_out,SIGNAL(clicked(bool)),this,SLOT(show_loginwindow()));
    this->close();
}

void LoginWindow::connect_sever()
{
    tcpsocket->abort();
    tcpsocket->connectToHost("127.0.0.1",19999,QTcpSocket::ReadWrite);
    qDebug()<<"连接服务器";
    qDebug()<<tcpsocket->waitForConnected();
}

void LoginWindow::closeEvent(QCloseEvent *event)
{
    if(login_return_list.size() != 3)
        tcpsocket->abort();
    login_return_list.clear();
    event->accept();
}
