#ifndef SIGNUP_H
#define SIGNUP_H

#include "headers.h"

extern QSqlDatabase database;
extern QVector<user_variable> all_users;
extern int max_id;
namespace Ui {
class signup;
}

class signup : public QDialog
{
    Q_OBJECT
    QSqlQuery sql_query;
public:
    explicit signup(QWidget *parent = 0);
    ~signup();

private slots:
    void on_signup_2_clicked();//点击注册按钮
private:
    Ui::signup *ui;
};

#endif // SIGNUP_H
