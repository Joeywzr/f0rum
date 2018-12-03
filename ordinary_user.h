#ifndef ORDINARY_USER_H
#define ORDINARY_USER_H
#include "user.h"
class MainWindow;
class Ordinary_user:public User
{
    Q_OBJECT
public:
    Ordinary_user();
    void init_class();//初始化
public slots:
    void user_information();//用户信息
private:

};

#endif // ORDINARY_USER_H
