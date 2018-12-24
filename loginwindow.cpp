#include "loginwindow.h"
#include "ui_loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    ui->sign_in->setFocus();
    this->setWindowTitle(QObject::tr("登录"));
    QFile file1( "user.txt" );
    file1.open( QFile::ReadOnly | QFile::Text );
    QTextStream fin1(&file1);
    user_variable users;
    fin1 >> users;
    file1.close();

    if(users.user_error != 0)
    {
        QString error = "存在"+QString::number(users.user_error)+"个用户数据出现错误，已删除错误用户数据！";
        QMessageBox::StandardButton button;
        button = QMessageBox::information(this, tr("提示"),
                                          error);
        users.user_error = 0;
    }

    QFile file2("post.txt");
    file2.open(QFile::ReadOnly | QFile::Text);
    QTextStream fin2(&file2);
    Post posts;
    fin2 >> posts;
    file2.close();
    if(posts.post_error != 0)
    {
        QString error = "存在"+QString::number(posts.post_error)+"个帖子数据出现错误，已删除错误帖子数据！";
        QMessageBox::StandardButton button;
        button = QMessageBox::information(this, tr("提示"),
                                          error);
        posts.post_error = 0;
    }
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
        qDebug() << all_users.size();
        int id;
        QString level;
        int responsible_plate;
        u = new User;
        bool judge = u->sign_in(username_input, password_input, username_flag, id, level, responsible_plate);
        //通过返回的judge来判断用户是否存在并获得正确的用户名与密码
        if(judge)
        {
            this->close();
            u = NULL;
            if(level == "administrator")//管理员登录
            {
                u = new Administrators;
                u->id = id;
                u->username = username_input;
                u->password = password_input;
                u->level = level;
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

void LoginWindow::on_anonymous_clicked()//点击匿名登录
{
    u = new Anonymous;
    u->id = -1;
    u->init_class();
    connect(u->mainview->ui->sign_out,SIGNAL(clicked(bool)),this,SLOT(show_loginwindow()));
    this->close();
}

void LoginWindow::closeEvent(QCloseEvent *event)
{
    QFile user("user.txt");

    user.open( QFile::ReadWrite | QFile :: Truncate );
    QTextStream fout1(&user);
    user_variable users;
    fout1 << users;
    user.close();

    event->accept();
}
