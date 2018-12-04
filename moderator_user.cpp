#include "moderator_user.h"

Moderator_user::Moderator_user()
{

}

void Moderator_user::user_information()//显示用户信息
{
    per_info = new Personal_infomation;
    per_info->username = username;
    per_info->id = id;
    per_info->level = level;
    per_info->show_respresponsible_plate = true;
    switch (responsible_plate) {
    case 1:
        per_info->responsible_plate = "游戏";break;
    case 2:
        per_info->responsible_plate = "电影";break;
    case 3:
        per_info->responsible_plate = "动漫";break;
    case 4:
        per_info->responsible_plate = "音乐";break;
    case 5:
        per_info->responsible_plate = "体育";break;
    default:
        break;
    }

    per_info->show_infomation();
    per_info->setModal(true);
    per_info->setWindowTitle(QObject::tr("个人信息"));
    per_info->show();
}
