#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <Personal_infomation.h>
#include <QLabel>
#include "registered_user.h"
#include "administrators.h"
#include "post.h"
#include "comment.h"
#include "writepostwindow.h"
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
    int id;
    int game_post_num = 0;
    QPushButton *button[13];
    ~MainWindow();

private slots:

    void on_personal_infomation_clicked();

    void on_sign_out_clicked();

    void on_game_clicked();

    void on_movie_clicked();

    void on_comic_clicked();

    void on_music_clicked();

    void on_sport_clicked();

    void on_post_clicked();

private:
    Ui::MainWindow *ui;
    Personal_infomation *per_info;
    Writepostwindow *push_post;
};

#endif // MAINWINDOW_H
