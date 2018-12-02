#include "moderator_user.h"

Moderator_user::Moderator_user()
{

}

void Moderator_user::init_class()
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

}

void Moderator_user::user_information()
{
    per_info = new Personal_infomation;
    per_info->username = username;
    per_info->id = id;
    per_info->level = level;
    per_info->show_respresponsible_plate = true;
    switch (responsible_plate) {
    case 1:
        per_info->responsible_plate = "game";break;
    case 2:
        per_info->responsible_plate = "movie";break;
    case 3:
        per_info->responsible_plate = "comic";break;
    case 4:
        per_info->responsible_plate = "music";break;
    case 5:
        per_info->responsible_plate = "sports";break;
    default:
        break;
    }

    per_info->show_infomation();
    per_info->setModal(true);
    per_info->setWindowTitle(QObject::tr("个人信息"));
    per_info->show();
}
