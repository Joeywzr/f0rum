#ifndef DETAILS_OF_POSTS_H
#define DETAILS_OF_POSTS_H

#include <QMainWindow>
#include <QSqlQuery>
#include <QMessageBox>
#include <QCloseEvent>
#include <QDate>
#include <QTime>
#include <QDateTime>
#include <QDebug>
#include "post.h"
extern QSqlDatabase database;
extern QHash<Category,QVector<Post>> all_post;
namespace Ui {
class Details_of_posts;
}

class Details_of_posts : public QMainWindow
{
    Q_OBJECT
public:
    explicit Details_of_posts(QWidget *parent = 0);
    ~Details_of_posts();

    Category state;
    int this_post_num;
    int responsible_plate;
    QString username;
    QString level;
    QSqlQuery sql_query;
    Post p;
    Ui::Details_of_posts *ui;

private slots:
    void on_comment_clicked();

    void on_quit_clicked();

    void on_delete_this_post_clicked();

    void closeEvent(QCloseEvent *event);

private:
};

#endif // DETAILS_OF_POSTS_H
