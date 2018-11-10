#include "personal_infomation.h"
#include "ui_personal_infomation.h"

Personal_infomation::Personal_infomation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Personal_infomation)
{
    ui->setupUi(this);
}

void Personal_infomation::show_infomation()
{
    ui->username->setText(username);
    ui->password->setText(password);
    ui->ID->setText(QString::number(id, 10));
}

Personal_infomation::~Personal_infomation()
{
    delete ui;
}
