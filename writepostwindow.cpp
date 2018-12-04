#include "writepostwindow.h"
#include "ui_writepostwindow.h"

Writepostwindow::Writepostwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Writepostwindow)
{
    ui->setupUi(this);
    ui->title->setMaxLength(30);
    ui->title->setFocus();
}

Writepostwindow::~Writepostwindow()
{
    delete ui;
}

void Writepostwindow::on_push_clicked()//点击发帖
{
    if(ui->title->text().isEmpty())
    {
        QMessageBox::StandardButton button;
        button = QMessageBox::information(this, tr("提示"),
                                          QString(tr("标题不能为空！")));
    }
    else if(ui->content->toPlainText().isEmpty())
    {
        QMessageBox::StandardButton button;
        button = QMessageBox::information(this, tr("提示"),
                                          QString(tr("内容不能为空！")));
    }
    else
    {
        QVector<Post> new_post = all_post.value(state);
        QDateTime local(QDateTime::currentDateTime());
        QString localTime = local.toString("yyyy-MM-dd:hh:mm:ss");
        Post p;
    //    int temp = p.id.toInt();
    //    temp++;
    //    p.id = QString::number(temp);
        p.title = ui->title->text();
        p.content = ui->content->toPlainText();
        p.time = localTime;
        p.poster_name = username;
        new_post.push_back(p);
        all_post.insert(state, new_post);
        ui->title->clear();
        ui->content->clear();
        this->close();
    }
}

void Writepostwindow::on_cancel_clicked()//点击取消
{
    if(ui->title->text().isEmpty() && ui->content->toPlainText().isEmpty())
    {
        ui->title->clear();
        ui->content->clear();
        this->close();
    }
    else
    {
        QMessageBox::StandardButton button;
        button = QMessageBox::question(this, tr("退出"),
                 QString(tr("有未发送的帖子，是否继续退出?")),
                 QMessageBox::Yes | QMessageBox::No);
        if (button == QMessageBox::Yes)
        {
                ui->title->clear();
                ui->content->clear();
                this->close();
        }
    }
}

void Writepostwindow::closeEvent(QCloseEvent *event)//点击右上角
{
    if(ui->title->text().isEmpty() && ui->content->toPlainText().isEmpty())
    {
        ui->title->clear();
        ui->content->clear();
    }
    else
    {
        QMessageBox::StandardButton button;
        button = QMessageBox::question(this, tr("退出"),
                 QString(tr("有未发送的帖子，是否继续退出?")),
                 QMessageBox::Yes | QMessageBox::No);

            if (button == QMessageBox::No) {
                event->ignore();  //忽略退出信号，程序继续运行
            }
            else if (button == QMessageBox::Yes) {
                ui->title->clear();
                ui->content->clear();
                event->accept();  //接受退出信号，程序退出
            }
    }
}

