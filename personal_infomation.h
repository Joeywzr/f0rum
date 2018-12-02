#ifndef PERSONAL_INFOMATION_H
#define PERSONAL_INFOMATION_H

#include <QDialog>

namespace Ui {
class Personal_infomation;
}

class Personal_infomation : public QDialog
{
    Q_OBJECT

public:
    QString username;
    int id;
    QString level;
    QString responsible_plate;
    bool show_respresponsible_plate;
    explicit Personal_infomation(QWidget *parent = 0);
    ~Personal_infomation();
    void show_infomation();

private:
    Ui::Personal_infomation *ui;
};

#endif // PERSONAL_INFOMATION_H
