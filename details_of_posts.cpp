#include "details_of_posts.h"
#include "ui_details_of_posts.h"
Details_of_posts::Details_of_posts(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Details_of_posts)
{
    ui->setupUi(this);
    ui->title->setStyleSheet("QLabel{text-align : left;"
                             "border:none;"
                             "color:blue;"
                             "font-weight: bold;}");
}

Details_of_posts::~Details_of_posts()
{
    delete ui;
}

void Details_of_posts::on_comment_clicked()
{
    if(ui->comment_edit->toPlainText().isEmpty())
    {
        QMessageBox::StandardButton button;
        button = QMessageBox::information(this, tr("提示"),QString(tr("评论不能为空！")));
    }
    else
    {
        QDateTime local(QDateTime::currentDateTime());
        QString localTime = local.toString("yyyy-MM-dd:hh:mm:ss");
        Comment comment_edit;
        comment_edit.content = ui->comment_edit->toPlainText();
        comment_edit.username = username;
        comment_edit.time = localTime;
        ui->comment_edit->clear();

        p.comment.push_back(comment_edit);

        QString all_content;
        all_content = ui->content->toPlainText();
        all_content.append("用户:" + comment_edit.username + "   发送时间:" + comment_edit.time + "\n\n");
        all_content.append(comment_edit.content + "\n\n");
        all_content.append("------------------------------------------\n\n");
        ui->content->setText(all_content);

        QVector<Post> temp = all_post[state];
        temp[this_post_num] = p;
        all_post[state] = temp;

        if(level == "ordinary" || (level == "moderator" && responsible_plate != state) )
            ui->delete_this_post->setEnabled(false);
    }
}

void Details_of_posts::on_quit_clicked()
{
    if(ui->comment_edit->toPlainText().isEmpty())
    {
        ui->title->clear();
        ui->content->clear();
        ui->comment_edit->clear();
        this->close();
    }
    else
    {
        QMessageBox::StandardButton button;
        button = QMessageBox::question(this, tr("退出"),
                                       QString(tr("有未发送的评论，是否继续退出?")),
                                       QMessageBox::Yes | QMessageBox::No);

        if (button == QMessageBox::Yes)
        {
            ui->title->clear();
            ui->content->clear();
            ui->comment_edit->clear();
            this->close();
        }
    }
}

void Details_of_posts::on_delete_this_post_clicked()
{
    QVector<Post> delete_post = all_post.value(state);
    qDebug() << this_post_num;
    delete_post.remove(this_post_num);
    all_post[state] = delete_post;
    ui->title->clear();
    ui->content->clear();
    ui->comment_edit->clear();
    this->close();
}

void Details_of_posts::closeEvent(QCloseEvent *event)
{
    if(ui->comment_edit->toPlainText().isEmpty())
    {
        ui->title->clear();
        ui->content->clear();
        ui->comment_edit->clear();
    }
    else
    {
        QMessageBox::StandardButton button;
        button = QMessageBox::question(this, tr("退出"),
                                       QString(tr("有未发送的评论，是否继续退出?")),
                                       QMessageBox::Yes | QMessageBox::No);

        if (button == QMessageBox::No)
        {
            event->ignore();  //忽略退出信号，程序继续运行
        }
        else if (button == QMessageBox::Yes)
        {
            ui->title->clear();
            ui->content->clear();
            ui->comment_edit->clear();
            event->accept();  //接受退出信号，程序退出
        }
    }
}
