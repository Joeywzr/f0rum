#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include "headers.h"
#include "user.h"
#include "administrators.h"
#include "ordinary_user.h"
#include "moderator_user.h"
#include "anonymous.h"
#include "post.h"
#include "signup.h"
extern QHash<Category,QVector<Post>> all_post;//所有帖子
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
//    Administrators *administrators;
//    Ordinary_user *ordinary_user;
//    Moderator_user *moderator_user;
    QSqlQuery sql_query;

private slots:
    void on_sign_in_clicked();//登录
    void on_sign_up_clicked();//注册
    void show_loginwindow();//打开登录窗口
    void on_anonymous_clicked();//匿名登录
    void closeEvent(QCloseEvent *event);//点击右上角退出

private:
    LoginWindow *new_mainview;
    signup *view;
    MainWindow *mainview;
    Ui::LoginWindow *ui;
};

#endif // LOGINWINDOW_H
