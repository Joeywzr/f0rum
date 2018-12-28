#include "administrators.h"

Administrators::Administrators()
{

}

void Administrators::init_class()//初始化
{
    mainview = new MainWindow;
    mainview->username = username;
    mainview->password = password;
    mainview->level = level;
    mainview->id = id;
    mainview->tcpsocket = tcpsocket;
    mainview->show();
    connect(mainview->ui->personal_infomation,SIGNAL(clicked(bool)), this, SLOT(user_information()));
    connect(mainview->ui->sign_out,SIGNAL(clicked(bool)), this, SLOT(sign_out()));
    connect(mainview->ui->appoint, SIGNAL(clicked(bool)),this,SLOT(appoint_or_revoke_moderator()));
    connect(mainview->ui->post, SIGNAL(clicked(bool)),this,SLOT(push_post()));
    connect(mainview->post_detail->ui->delete_this_post, SIGNAL(clicked(bool)),this,SLOT(refresh()));
    connect(mainview->tcpsocket,SIGNAL(disconnected()),this,SLOT(ddisconnected()));
}

void Administrators::user_information()//用户信息
{
    per_info = new Personal_infomation;
    per_info->username = username;
    per_info->id = id;
    per_info->level = level;
    per_info->show_respresponsible_plate = false;
    per_info->show_infomation();
    per_info->setModal(true);
    per_info->setWindowTitle(QObject::tr("个人信息"));
    per_info->show();
}

void Administrators::appoint_or_revoke_moderator()//任命或撤销版主
{
    mod = new Moderatorwindow(mainview->state);
    QString temp;
    if(mod->state == 1)
        temp = "新手乐园";
    else if(mod->state == 2)
        temp = "技术交流";
    else if(mod->state == 3)
        temp = "资源共享";
    else if(mod->state == 4)
        temp = "休闲娱乐";
    else if(mod->state == 5)
        temp = "账号申诉";
    mod->ui->state->setText("当前板块:" + temp);
    mod->setWindowTitle(QObject::tr(""));
    mod->setWindowModality(Qt::ApplicationModal);
    mod->show();
}
