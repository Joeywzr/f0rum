#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include "signup.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "moderator_user.h"
#include "post.h"
#include "user.h"

extern QSqlDatabase database;
extern QVector<user_variable> all_users;
namespace Ui {
class LoginWindow;
}

class LoginWindow : public QWidget
{
    Q_OBJECT
    QSqlQuery sql_query;
public:
    explicit LoginWindow(QWidget *parent = 0);
    Administrators *administrators;
    Ordinary_user *ordinary_user;
    Moderator_user *moderator_user;
    Ui::LoginWindow *ui;
    ~LoginWindow();


private slots:
    void on_sign_in_clicked();
    void on_sign_up_clicked();
    void show_loginwindow();

private:
    LoginWindow *new_mainview;

    signup *view;
    MainWindow *mainview;
};

#endif // LOGINWINDOW_H
