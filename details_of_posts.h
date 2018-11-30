#ifndef DETAILS_OF_POSTS_H
#define DETAILS_OF_POSTS_H

#include <QMainWindow>
#include "post.h"
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
    QString time_now;

    Post p;
    explicit Details_of_posts(QWidget *parent = 0);
    ~Details_of_posts();
    Ui::Details_of_posts *ui;



private slots:
    void on_comment_clicked();

    void on_quit_clicked();

private:
};

#endif // DETAILS_OF_POSTS_H
