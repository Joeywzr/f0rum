#ifndef MODERATOR_USER_H
#define MODERATOR_USER_H
#include "ordinary_user.h"
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
class Moderator_user:public Ordinary_user
{
    Q_OBJECT
public:
    Moderator_user();

    void init_class();
public slots:
    void user_information();
};

#endif // MODERATOR_USER_H
