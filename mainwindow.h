#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "headers.h"
#include "post.h"
#include "writepostwindow.h"
#include "details_of_posts.h"
#include "personal_infomation.h"
#include "ui_details_of_posts.h"
#include "ui_writepostwindow.h"
extern QHash<Category,QVector<Post>> all_post;
extern QVector<user_variable> all_users;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    int responsible_plate = 0;
    int id;
    int page_post_num = 0;
    int state_post_num;
    Category state;
    QString username;
    QString password;
    QString level;
    QPushButton *button[13];
    Ui::MainWindow *ui;

    Details_of_posts *post_detail;
    QButtonGroup *bg;
private slots:

    void on_game_clicked();//点击游戏板块

    void on_movie_clicked();//点击电影板块

    void on_comic_clicked();//点击动漫板块

    void on_music_clicked();//点击音乐板块

    void on_sport_clicked();//点击体育板块

    void on_next_page_clicked();//点击下一页

    void on_back_clicked();//点击上一页

    void click_posts(int i);//点击帖子

    void closeEvent(QCloseEvent *event);//点击右上角退出
};

#endif // MAINWINDOW_H
