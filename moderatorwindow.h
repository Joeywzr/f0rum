#ifndef MODERATORWINDOW_H
#define MODERATORWINDOW_H

#include <QMainWindow>
#include <QCheckBox>
#include <QButtonGroup>
#include <QDebug>
#include <QDialog>
#include "user.h"
#include "post.h"

extern QVector<user_variable> all_users;
namespace Ui {
class Moderatorwindow;
}

class Moderatorwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit Moderatorwindow(Category s,QWidget *parent = 0
                             );

    QCheckBox *button[13];
    QButtonGroup *bg;
    int page_num = 0;
    int user_num;
    Category state;
    Ui::Moderatorwindow *ui;


    ~Moderatorwindow();



private slots:
    void click_users(int i );
    void on_next_page_clicked();
    void on_back_clicked();
    void on_pushButton_clicked();

private:

};

#endif // MODERATORWINDOW_H
