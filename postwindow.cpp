#include "postwindow.h"
#include "ui_postwindow.h"

Postwindow::Postwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Postwindow)
{
    ui->setupUi(this);
}

Postwindow::~Postwindow()
{
    delete ui;
}
