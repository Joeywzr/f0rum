#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include "headers.h"
#include "user.h"
#include "administrators.h"
#include "ordinary_user.h"
#include "moderator_user.h"
#include "post.h"
#include "signup.h"

extern QSqlDatabase database;
extern QVector<user_variable> all_users;
namespace Ui {
class LoginWindow;
}

class LoginWindow : public QWidget
{
    Q_OBJECT
public:
    explicit LoginWindow(QWidget *parent = 0);
    ~LoginWindow();

    User *u;
    Administrators *administrators;
    Ordinary_user *ordinary_user;
    Moderator_user *moderator_user;
    QSqlQuery sql_query;

private slots:
    void on_sign_in_clicked();//登录
    void on_sign_up_clicked();//注册
    void show_loginwindow();//打开登录窗口

private:
    LoginWindow *new_mainview;
    signup *view;
    MainWindow *mainview;
    Ui::LoginWindow *ui;
};

#endif // LOGINWINDOW_H
