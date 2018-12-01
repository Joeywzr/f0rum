#ifndef WRITEPOSTWINDOW_H
#define WRITEPOSTWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QMessageBox>
#include <QDate>
#include <QTime>
#include <QDateTime>
#include "post.h"
extern QHash<Category,QVector<Post>> all_post;
namespace Ui {
class Writepostwindow;
}

class Writepostwindow : public QMainWindow
{
    Q_OBJECT



public:
    Category state;
    QString username;
    explicit Writepostwindow(QWidget *parent = 0);
    ~Writepostwindow();
    Post a;
    Ui::Writepostwindow *ui;

private slots:
    void on_push_clicked();

    void on_cancel_clicked();

    void closeEvent(QCloseEvent *event);

private:
};

#endif // WRITEPOSTWINDOW_H
