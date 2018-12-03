#ifndef MODERATOR_USER_H
#define MODERATOR_USER_H
#include "ordinary_user.h"
class MainWindow;
class Moderator_user:public Ordinary_user
{
    Q_OBJECT
public:
    Moderator_user();
public slots:
    void user_information();//用户信息
};

#endif // MODERATOR_USER_H
