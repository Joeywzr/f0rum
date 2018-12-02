#ifndef USER_H
#define USER_H
#include <QMainWindow>
#include <QLabel>
#include <QObject>
#include <QVector>
#include <QString>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include <QDebug>
#include "post.h"
extern QSqlDatabase database;
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
    int responsible_plate;
    QString username;
    QString password;
    QString level;
    QSqlQuery sql_query;
    //-------基础要求----------//

    //------------------------//
public slots:
    virtual void user_information(){}
    bool sign_in(QString username_input, QString password_input,
                 bool &username_flag, int &id, QString &level,
                 int &responsible_plate);
    virtual void sign_out(){}

};

#endif // USER_H
