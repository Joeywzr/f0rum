#ifndef USER_H
#define USER_H
#include <QVector>
#include <QString>
class User
{
public:
    User();
    int id;
    QString username;
    QString password;
    QString level;

//-------基础要求----------//
    virtual void user_information() = 0;
    virtual void sign_in() = 0;
    virtual void sign_out() = 0;
    virtual void check() = 0;
//------------------------//

};

#endif // USER_H
