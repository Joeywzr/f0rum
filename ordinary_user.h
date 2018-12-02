#ifndef ORDINARY_USER_H
#define ORDINARY_USER_H
#include <user.h>
#include <QDebug>
#include <QWidget>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include "mainwindow.h"
#include "ui_mainwindow.h"

class MainWindow;
class Ordinary_user:public User
{
    Q_OBJECT
public:
    Ordinary_user();
    MainWindow *mainview;
    //-------åŸºç¡€è¦æ±‚----------//
    virtual void user_information();
    virtual void sign_in();
    virtual void sign_out();
    virtual void check();
    void post();
    void comment();
    void delete_my_post();
    //-------é™„åŠ åŠŸèƒ½----------//
    void sign_up();

    //-------ç‰ˆä¸»-------------//
    void delete_post();
    //-----------------------//
private:

};

#endif // ORDINARY_USER_H
