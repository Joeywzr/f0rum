#ifndef MODERATORWINDOW_H
#define MODERATORWINDOW_H

#include "headers.h"

extern QVector<user_variable> all_users;
namespace Ui {
class Moderatorwindow;
}

class Moderatorwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit Moderatorwindow(Category s,QWidget *parent = 0);
    ~Moderatorwindow();

    int page_num = 0;
    int user_num;
    QCheckBox *button[13];
    QButtonGroup *bg;
    Category state;
    Ui::Moderatorwindow *ui;

private slots:
    void click_users(int i );//点击用户名
    void on_next_page_clicked();//点击下一页
    void on_back_clicked();//点击上一页
    void on_quit_clicked();//点击关闭

private:

};

#endif // MODERATORWINDOW_H
