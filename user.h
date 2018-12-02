#ifndef USER_H
#define USER_H

#include <QObject>
#include <QVector>
#include <QString>

typedef struct USER_VAR
{
    int id;
    QString username;
    QString password;
    QString level;
    int responsible_plate;
}user_variable;

class User : public QObject
{
    Q_OBJECT
public:
    explicit User(QObject *parent = nullptr);
    int id;
    QString username;
    QString password;
    QString level;
    int responsible_plate;
    //-------基础要求----------//

    //------------------------//
signals:

public slots:
    virtual void user_information() = 0;
    virtual void sign_in() = 0;
    virtual void sign_out() = 0;

};

#endif // USER_H
