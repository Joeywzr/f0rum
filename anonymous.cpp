#include "anonymous.h"

Anonymous::Anonymous()
{

}

void Anonymous::init_class()
{
    mainview = new MainWindow;
    mainview->username = "匿名";
    mainview->id = id;
    mainview->tcpsocket = tcpsocket;
    mainview->ui->post->setEnabled(false);
    mainview->ui->appoint->setEnabled(false);
    mainview->show();
    connect(mainview->ui->personal_infomation,SIGNAL(clicked(bool)), this, SLOT(user_information()));
    connect(mainview->ui->sign_out,SIGNAL(clicked(bool)), this, SLOT(sign_out()));
    connect(mainview->post_detail->ui->delete_this_post, SIGNAL(clicked(bool)),this,SLOT(refresh()));
}

void Anonymous::user_information()
{
    per_info = new Personal_infomation;
    per_info->username = "匿名";
    per_info->id = id;
    per_info->show_infomation();
    per_info->setModal(true);
    per_info->setWindowTitle(QObject::tr("个人信息"));
    per_info->show();
}
