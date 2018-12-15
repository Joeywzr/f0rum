#include "user.h"

User::User(QObject *parent) : QObject(parent)
{

}

void User::init_class()//初始化
{
    mainview = new MainWindow;
    mainview->username = username;
    mainview->password = password;
    mainview->level = level;
    mainview->id = id;
    mainview->show();
    connect(mainview->ui->personal_infomation,SIGNAL(clicked(bool)), this, SLOT(user_information()));
    connect(mainview->ui->sign_out,SIGNAL(clicked(bool)), this, SLOT(sign_out()));
    connect(mainview->ui->appoint, SIGNAL(clicked(bool)),this,SLOT(appoint_or_revoke_moderator()));
    connect(mainview->ui->post, SIGNAL(clicked(bool)),this,SLOT(push_post()));
    connect(mainview->post_detail->ui->delete_this_post, SIGNAL(clicked(bool)),this,SLOT(refresh()));
}

void User::push_post()//发帖
{
    writepost = new Writepostwindow;
    writepost->state = mainview->state;
    writepost->username = username;
    Post a;
    writepost->a = a;
    writepost->setWindowModality(Qt::ApplicationModal);
    writepost->setWindowTitle(QObject::tr("发帖"));
    connect(writepost->ui->push, SIGNAL(clicked(bool)), this, SLOT(refresh()));
    writepost->show();
}

void User::refresh()//刷新
{
    mainview->page_post_num = 0;
    for(int i = 0;i <= 12;i++)
    {
        mainview->button[i]->setText("");
        mainview->button[i]->setEnabled(false);
    }
    QVector<Post> posts = all_post.value(mainview->state);
    mainview->state_post_num = posts.size() - 1;
    for(int i = 0;i <= 12 && mainview->state_post_num >= 0;i++)
    {
        mainview->button[i]->setEnabled(true);
        mainview->button[i]->setText(posts[mainview->state_post_num--].title);
    }
}

void User::sign_out()//注销
{
    mainview->close();
}

bool User::sign_in(QString username_input, QString password_input,
                   bool &username_flag, int &id, QString &level,
                   int &responsible_plate)//登录
{
    user_variable u;
    for(int i = 0;i < all_users.size();i++)
    {
        u = all_users[i];
        if(username_input == u.username)
        {
            username_flag = true;
            if(password_input == u.password)
            {
                level = u.level;
                responsible_plate = u.responsible_plate;
                id = u.id;
                return true;
            }
            return false;
        }
    }
    return false;
}

