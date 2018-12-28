#ifndef USER_H
#define USER_H
#include "headers.h"
#include "signup.h"
#include "mainwindow.h"
#include "moderatorwindow.h"
#include "personal_infomation.h"
#include "post.h"
#include "ui_mainwindow.h"
#include "ui_moderatorwindow.h"

class User : public QObject
{
    Q_OBJECT
public:

    explicit User(QObject *parent = nullptr);
    int id;//id
    int responsible_plate;//负责板块（仅版主）
    QString username;//用户名
    QString password;//密码
    QString level;//级别
    QTcpSocket *tcpsocket;

    MainWindow *mainview;
    Personal_infomation *per_info;
    Moderatorwindow *mod;
    Writepostwindow *writepost;

    virtual void init_class();//初始化

public slots:
    virtual void user_information(){}//用户信息
    void ddisconnected();
    void sign_out();//注销
    void push_post();//发帖
    void refresh();//刷新
    bool sign_in(QString username_input, QString password_input,
                 bool &username_flag, int &id, QString &level,
                 int &responsible_plate);//登录
};

#endif // USER_H
