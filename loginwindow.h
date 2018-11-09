#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include "signup.h"

extern QSqlDatabase database;

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = 0);
    ~LoginWindow();
    void click_sign_in();

private slots:
    void on_sign_in_clicked();

    void on_sign_up_clicked();

private:
    Ui::LoginWindow *ui;
    signup *view;
};

#endif // LOGINWINDOW_H
