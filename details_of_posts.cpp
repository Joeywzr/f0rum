#include "details_of_posts.h"
#include "ui_details_of_posts.h"
#include <QDebug>
Details_of_posts::Details_of_posts(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Details_of_posts)
{
    ui->setupUi(this);
//    ui->title->setText();
}

Details_of_posts::~Details_of_posts()
{
    delete ui;
}

void Details_of_posts::on_comment_clicked()
{
    Comment comment_edit;
    comment_edit.content = ui->comment_edit->toPlainText();
    comment_edit.username = username;
    comment_edit.time = time_now;
    ui->comment_edit->clear();

    p.comment.push_back(comment_edit);

    QString all_content;
    all_content = ui->content->toPlainText();
    all_content.append("用户:");
    all_content.append(comment_edit.username + "\n\n");
    all_content.append(comment_edit.content + "\n\n");
    all_content.append("------------------------------------------\n\n");
    ui->content->setText(all_content);

    QVector<Post> temp = all_post[state];
    temp[this_post_num] = p;
    all_post[state] = temp;
}

void Details_of_posts::on_quit_clicked()
{
    this->close();
}
