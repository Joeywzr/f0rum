#include "loginwindow.h"
#include "ui_loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    ui->sign_in->setFocus();
    this->setWindowTitle(QObject::tr("登录"));
    //-------------------------看看所有用户----------------------
            QString select_all_sql = "select * from users";
            sql_query.prepare(select_all_sql);
            if(!sql_query.exec())
            {
                qDebug()<<sql_query.lastError();
            }
            else
            {
                while(sql_query.next())
                {
                    int id = sql_query.value(0).toInt();
                    QString username = sql_query.value(1).toString();
                    QString password = sql_query.value(2).toString();
                    QString level = sql_query.value(3).toString();
                    int responsible_plate = sql_query.value(4).toInt();
                    qDebug()<<QString("id:%1    username:%2    password:%3   level:%4   responsible_plate:%5").arg(id).arg(username).arg(password).arg(level).arg(responsible_plate);
                }
            }
    //--------------------------------------------------------------------
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_sign_in_clicked()//点击登录按钮
{
    QString username_input = ui->username->text();
    QString password_input = ui->password->text();
    bool username_flag = false;
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
        QString select_sql = "select id, username,password, level, responsible_plate from users";
        if(!sql_query.exec(select_sql))
            qDebug()<<sql_query.lastError();
        else
        {
            int id;
            QString level;
            int responsible_plate;
            u = new User;
            bool judge = u->sign_in(username_input, password_input, username_flag, id, level, responsible_plate);
            //通过返回的judge来判断用户是否存在并获得正确的用户名与密码
            if(judge)
            {
                QString select_sql = "select id, username,password, level, responsible_plate from users";
                if(!sql_query.exec(select_sql))
                    qDebug()<<sql_query.lastError();
                else
                {
                    while(sql_query.next())
                    {
                        user_variable uu;
                        uu.id = sql_query.value(0).toInt();
                        uu.username = sql_query.value(1).toString();
                        uu.password = sql_query.value(2).toString();
                        uu.level = sql_query.value(3).toString();
                        uu.responsible_plate = sql_query.value(4).toInt();
                        all_users.push_back(uu);
                    }
                }
                this->close();
                u = NULL;
                if(id <= 5)//管理员登录
                {
                    u = new Administrators;
                    u->id = id;
                    u->username = username_input;
                    u->password = password_input;
                    u->level = level;
                    u->init_class();
                    connect(u->mainview->ui->sign_out,SIGNAL(clicked(bool)),this,SLOT(show_loginwindow()));
                }
                else if(id > 5 && level == "ordinary")//普通用户登录
                {
                    u = new Ordinary_user;
                    u->id = id;
                    u->username = username_input;
                    u->password = password_input;
                    u->level = level;
                    u->responsible_plate = responsible_plate;
                    u->init_class();
                    connect(u->mainview->ui->sign_out,SIGNAL(clicked(bool)),this,SLOT(show_loginwindow()));
                }
                else if(id > 5 && level == "moderator")//版主登录
                {
                    u = new Moderator_user;
                    u->id = id;
                    u->username = username_input;
                    u->password = password_input;
                    u->level = level;
                    u->responsible_plate = responsible_plate;
                    u->init_class();
                    connect(u->mainview->ui->sign_out,SIGNAL(clicked(bool)),this,SLOT(show_loginwindow()));
                }
            }
            else
            {
                if(!username_flag)
                {
                    ui->username->setText(NULL);
                    ui->password->setText(NULL);
                    ui->warning->setText("用户名不存在！");
                    qDebug() << "Username doesn't exist!";
                    return;
                }
                else
                {
                    ui->warning->setText("密码错误！请重试！");
                    qDebug() << "Password is wrong.Please try again.";
                    ui->password->setText(NULL);
                    return;
                }
            }
        }
    }
}

void LoginWindow::on_sign_up_clicked()//点击注册按钮
{
    view = new signup(this);
    view->setModal(true);
    view->show();
}

void LoginWindow::show_loginwindow()//显示登录界面
{
    new_mainview = new LoginWindow;
    new_mainview->show();
}
