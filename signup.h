#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>

namespace Ui {
class signup;
}

class signup : public QDialog
{
    Q_OBJECT

public:
    explicit signup(QWidget *parent = 0);
    ~signup();

private:
    Ui::signup *ui;
};

#endif // SIGNUP_H
