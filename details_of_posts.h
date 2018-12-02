#ifndef DETAILS_OF_POSTS_H
#define DETAILS_OF_POSTS_H

#include <QMainWindow>
#include <QSqlQuery>
#include <QMessageBox>
#include <QCloseEvent>
#include <QDate>
#include <QTime>
#include <QDateTime>
#include "post.h"
extern QSqlDatabase database;
extern QSqlQuery sql_query;
extern QHash<Category,QVector<Post>> all_post;
namespace Ui {
class Details_of_posts;
}

class Details_of_posts : public QMainWindow
{
    Q_OBJECT

public:
    Category state;
    int this_post_num;
    QString username;
    QString level;
    int responsible_plate;

    Post p;
    explicit Details_of_posts(QWidget *parent = 0);
    ~Details_of_posts();
    Ui::Details_of_posts *ui;



private slots:
    void on_comment_clicked();

    void on_quit_clicked();

    void on_delete_this_post_clicked();

    void closeEvent(QCloseEvent *event);

private:
};

#endif // DETAILS_OF_POSTS_H
