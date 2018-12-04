#include "ordinary_user.h"

Ordinary_user::Ordinary_user()
{

}

void Ordinary_user::init_class()//初始化
{
    mainview = new MainWindow;
    mainview->username = username;
    mainview->password = password;
    mainview->level = level;
    mainview->id = id;
    mainview->responsible_plate = responsible_plate;
    mainview->ui->appoint->setEnabled(false);
    mainview->show();
    connect(mainview->ui->personal_infomation,SIGNAL(clicked(bool)), this, SLOT(user_information()));
    connect(mainview->ui->sign_out,SIGNAL(clicked(bool)), this, SLOT(sign_out()));
    connect(mainview->ui->post, SIGNAL(clicked(bool)),this,SLOT(push_post()));
    connect(mainview->post_detail->ui->delete_this_post, SIGNAL(clicked(bool)),this,SLOT(refresh()));
}

void Ordinary_user::user_information()//显示用户信息
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

