#include "loginwindow.h"
#include "ui_loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(QObject::tr("登录"));
    if (!database.open())
        qDebug() << "Error: Failed to connect database." << database.lastError();
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

void LoginWindow::on_sign_in_clicked()
{
    QString username_input = ui->username->text();
    QString password_input = ui->password->text();
    bool username_flag = false;
    if(username_input.isEmpty())
    {
        ui->warning->setText("Please input username!");
        qDebug() << "Please input username!";
        return;
    }
    else if(password_input.isEmpty())
    {
        ui->warning->setText("Please input password!");
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
            User *u;
            u = new User;
            bool judge = u->sign_in(username_input, password_input, username_flag, id, level, responsible_plate);

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
                if(id <= 5)
                {
                    administrators = new Administrators;
                    administrators->id = id;
                    administrators->username = username_input;
                    administrators->password = password_input;
                    administrators->level = level;
                    administrators->init_class();
                    connect(administrators->mainview->ui->sign_out,SIGNAL(clicked(bool)),this,SLOT(show_loginwindow()));
                }
                else if(id > 5 && level == "ordinary")
                {
                    ordinary_user = new Ordinary_user;
                    ordinary_user->id = id;
                    ordinary_user->username = username_input;
                    ordinary_user->password = password_input;
                    ordinary_user->level = level;
                    ordinary_user->responsible_plate = responsible_plate;
                    ordinary_user->init_class();
                    connect(ordinary_user->mainview->ui->sign_out,SIGNAL(clicked(bool)),this,SLOT(show_loginwindow()));
                }
                else if(id > 5 && level == "moderator")
                {
                    moderator_user = new Moderator_user;
                    moderator_user->id = id;
                    moderator_user->username = username_input;
                    moderator_user->password = password_input;
                    moderator_user->level = level;
                    moderator_user->responsible_plate = responsible_plate;
                    moderator_user->init_class();
                    connect(moderator_user->mainview->ui->sign_out,SIGNAL(clicked(bool)),this,SLOT(show_loginwindow()));
                }
            }
            else
            {
                if(!username_flag)
                {
                    ui->username->setText(NULL);
                    ui->password->setText(NULL);
                    ui->warning->setText("Username doesn't exist!");
                    qDebug() << "Username doesn't exist!";
                    return;
                }
                else
                {
                    ui->warning->setText("Password is wrong.Please try again.");
                    qDebug() << "Password is wrong.Please try again.";
                    ui->password->setText(NULL);
                    return;
                }
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

void LoginWindow::show_loginwindow()
{
    new_mainview = new LoginWindow;
    new_mainview->show();
}
