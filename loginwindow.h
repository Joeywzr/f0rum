#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include "signup.h"
#include "mainwindow.h"

extern QSqlDatabase database;

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QWidget
{
    Q_OBJECT
    QSqlQuery sql_query;
public:
    explicit LoginWindow(QWidget *parent = 0);
    ~LoginWindow();


private slots:
    void on_sign_in_clicked();
    void on_sign_up_clicked();

private:
    Ui::LoginWindow *ui;
    signup *view;
    MainWindow *mainview;
};

#endif // LOGINWINDOW_H
