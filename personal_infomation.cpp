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
    ui->id->setText(QString::number(id, 10));
    ui->level->setText(level);
    if(show_respresponsible_plate)
        ui->responsible->setText(responsible_plate);
    else
    {
        ui->responsible->setEnabled(false);
        ui->res_title->setEnabled(false);
    }
}

Personal_infomation::~Personal_infomation()
{
    delete ui;
}
