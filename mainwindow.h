#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "Personal_infomation.h"
#include <QLabel>
#include <QButtonGroup>
#include <QDate>
#include <QTime>
#include <QDateTime>
#include "ordinary_user.h"
#include "administrators.h"
#include "post.h"
#include "comment.h"
#include "writepostwindow.h"
#include "details_of_posts.h"
#include "ui_details_of_posts.h"
#include "ui_writepostwindow.h"
extern QHash<Category,QVector<Post>> all_post;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);
    Category state;
    QString username;
    QString password;
    QString level;
    int responsible_plate = 0;
    int id;
    int page_post_num = 0;
    int state_post_num;
    QPushButton *button[13];
    Ui::MainWindow *ui;
    ~MainWindow();

private slots:

    void on_game_clicked();

    void on_movie_clicked();

    void on_comic_clicked();

    void on_music_clicked();

    void on_sport_clicked();

    void on_post_clicked();

    void on_next_page_clicked();

    void on_back_clicked();

    void refresh();

    void click_posts(int i);

private:

    Personal_infomation *per_info;
    Writepostwindow *push_post;
    Details_of_posts *post_detail;
    QButtonGroup *bg;
};

#endif // MAINWINDOW_H
