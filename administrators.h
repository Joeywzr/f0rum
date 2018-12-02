#ifndef ADMINISTRATORS_H
#define ADMINISTRATORS_H
#include <QObject>
#include <user.h>
#include <QDebug>
#include <QWidget>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include "signup.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "moderatorwindow.h"
#include "ui_moderatorwindow.h"
#include "moderatorwindow.h"
#include "ui_moderatorwindow.h"
#include "post.h"
extern QVector<user_variable> all_users;

class MainWindow;
class Administrators:public User
{
    Q_OBJECT
public:
    Administrators(QString username_input,
                   QString password_input,
                   int id_input,
                   QString level_input);
    MainWindow *mainview;
    Personal_infomation *per_info;
    Moderatorwindow *mod;

    //-------基础要求----------//


public slots:
    void user_information();
    void sign_out();
    void sign_in();
    void appoint_or_revoke_moderator();
    //------------------------//
private:

};

#endif // ADMINISTRATORS_H
