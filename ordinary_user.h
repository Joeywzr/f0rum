#ifndef ORDINARY_USER_H
#define ORDINARY_USER_H
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

class MainWindow;
class Ordinary_user:public User
{
    Q_OBJECT
public:
    Ordinary_user();
    MainWindow *mainview;
    Personal_infomation *per_info;

    void init_class();

public slots:
    void user_information();
    void sign_out();
private:

};

#endif // ORDINARY_USER_H
