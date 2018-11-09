#ifndef USER_H
#define USER_H
#include <QVector>
#include <QString>

typedef struct info
{
    int id;
    QString userName;
    QString password;
}INFO;

class User
{
public:
    User();

//-------基础要求----------//
    virtual void user_information() = 0;
    virtual void sign_in() = 0;
    virtual void sign_out() = 0;
    virtual void check() = 0;
//------------------------//

};

#endif // USER_H
