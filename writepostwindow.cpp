#include "writepostwindow.h"
#include "ui_writepostwindow.h"

Writepostwindow::Writepostwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Writepostwindow)
{
    ui->setupUi(this);
}

Writepostwindow::~Writepostwindow()
{
    delete ui;
}

void Writepostwindow::on_push_clicked()
{
    QVector<Post> new_post = all_post.value(state);
    Post p;
//    int temp = p.id.toInt();
//    temp++;
//    p.id = QString::number(temp);
    p.title = ui->title->toPlainText();
    p.content = ui->content->toPlainText();
    p.poster_name = username;
    new_post.push_back(p);
    all_post.insert(state, new_post);
    this->close();
}

void Writepostwindow::on_cancel_clicked()
{
    this->close();
}
