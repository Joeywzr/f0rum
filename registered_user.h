#ifndef REGISTERED_USER_H
#define REGISTERED_USER_H
#include <user.h>

class Registered_user:public User
{
public:
    Registered_user();

    QVector<INFO> info;

    //-------基础要求----------//
    virtual void user_information(int my_id);
    virtual void sign_in();
    virtual void sign_out();
    virtual void check();
    void post();
    void comment();
    void delete_my_post();
    //-------附加功能----------//
    void sign_up();

    //-------版主-------------//
    void delete_post();
    //-----------------------//
};

#endif // REGISTERED_USER_H
