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
        per_info->responsible_plate = "新手乐园";break;
    case 2:
        per_info->responsible_plate = "技术交流";break;
    case 3:
        per_info->responsible_plate = "资源共享";break;
    case 4:
        per_info->responsible_plate = "休闲娱乐";break;
    case 5:
        per_info->responsible_plate = "账号申诉";break;
    default:
        break;
    }

    per_info->show_infomation();
    per_info->setModal(true);
    per_info->setWindowTitle(QObject::tr("个人信息"));
    per_info->show();
}
