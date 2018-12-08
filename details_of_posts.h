#ifndef DETAILS_OF_POSTS_H
#define DETAILS_OF_POSTS_H

#include "headers.h"
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

    Post p;
    int this_post_num;//该帖子在该板块中的序号
    int id;//当前用户id
    int responsible_plate;
    Category state;
    QString username;
    QString level;
    QSqlQuery sql_query;
    Ui::Details_of_posts *ui;

private slots:
    void on_comment_clicked();//点击评论按钮

    void on_quit_clicked();//点击退出按钮

    void on_delete_this_post_clicked();//点击删帖按钮

    void closeEvent(QCloseEvent *event);//点击右上角退出按钮

};

#endif // DETAILS_OF_POSTS_H
