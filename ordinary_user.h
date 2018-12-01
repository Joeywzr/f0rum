#ifndef ORDINARY_USER_H
#define ORDINARY_USER_H
#include <user.h>

class Ordinary_user:public User
{
public:
    Ordinary_user();

    //-------基础要求----------//
    virtual void user_information();
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

#endif // ORDINARY_USER_H
