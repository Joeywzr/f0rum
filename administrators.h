#ifndef ADMINISTRATORS_H
#define ADMINISTRATORS_H
#include "user.h"

extern QVector<user_variable> all_users;

class MainWindow;
class Administrators:public User
{
    Q_OBJECT
public:
    Administrators();
    void init_class();//初始化
public slots:
    void user_information();//用户信息
    void appoint_or_revoke_moderator();//任命或撤销版主
};

#endif // ADMINISTRATORS_H
