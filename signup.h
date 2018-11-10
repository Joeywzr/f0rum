#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

extern QSqlDatabase database;
extern int max_id;
namespace Ui {
class signup;
}

class signup : public QDialog
{
    Q_OBJECT

public:

    explicit signup(QWidget *parent = 0);
    ~signup();

private slots:

    void on_signup_2_clicked();

private:
    Ui::signup *ui;
};

#endif // SIGNUP_H
