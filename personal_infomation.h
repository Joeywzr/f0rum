#ifndef PERSONAL_INFOMATION_H
#define PERSONAL_INFOMATION_H

#include "headers.h"

namespace Ui {
class Personal_infomation;
}

class Personal_infomation : public QDialog
{
    Q_OBJECT

public:
    explicit Personal_infomation(QWidget *parent = 0);
    ~Personal_infomation();

    int id;
    QString username;
    QString level;
    QString responsible_plate;
    bool show_respresponsible_plate;

    void show_infomation();//显示个人信息

private:
    Ui::Personal_infomation *ui;
};

#endif // PERSONAL_INFOMATION_H
