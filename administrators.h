#ifndef ADMINISTRATORS_H
#define ADMINISTRATORS_H
#include <user.h>
#include <QDebug>

class Administrators:public User
{
public:
    Administrators();
    INFO info;

    //-------基础要求----------//
    virtual void user_information();
    virtual void sign_in();
    virtual void sign_out();
    virtual void check();
    void appoint_moderator();
    void revoked_moderator();

    //------------------------//

};

#endif // ADMINISTRATORS_H
