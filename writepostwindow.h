#ifndef WRITEPOSTWINDOW_H
#define WRITEPOSTWINDOW_H

#include "headers.h"
#include "post.h"
extern QHash<Category,QVector<Post>> all_post;
namespace Ui {
class Writepostwindow;
}

class Writepostwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit Writepostwindow(QWidget *parent = 0);
    ~Writepostwindow();

    Post a;
    Category state;
    QString username;
    Ui::Writepostwindow *ui;

private slots:
    void on_push_clicked();//点击发帖
    void on_cancel_clicked();//点击取消
    void closeEvent(QCloseEvent *event);//点击右上角退出
};

#endif // WRITEPOSTWINDOW_H
