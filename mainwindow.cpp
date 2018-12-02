#define post_display_num 13
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    button[0] = ui->pushButton_1;
    button[1] = ui->pushButton_2;
    button[2] = ui->pushButton_3;
    button[3] = ui->pushButton_4;
    button[4] = ui->pushButton_5;
    button[5] = ui->pushButton_6;
    button[6] = ui->pushButton_7;
    button[7] = ui->pushButton_8;
    button[8] = ui->pushButton_9;
    button[9] = ui->pushButton_10;
    button[10] = ui->pushButton_11;
    button[11] = ui->pushButton_12;
    button[12] = ui->pushButton_13;
    for(int i = 0;i < post_display_num; i++)
    {
        button[i]->setStyleSheet("border:none;");
        button[i]->setEnabled(false);
    }

    bg = new QButtonGroup;
    push_post = new Writepostwindow(this);
    post_detail = new Details_of_posts(this);
    for(int i = 0;i <= 12;i++)
        bg->addButton(button[i],i);

    state = game;
    ui->game->setChecked(true);
    ui->game->setCheckable(true);
    ui->game->setAutoExclusive(true);

    page_post_num = 0;
    for(int i = 0;i <= 12;i++)
    {
        button[i]->setText("");
        button[i]->setEnabled(false);
    }
    state = game;
    QVector<Post> game_posts = all_post.value(state);
    state_post_num = game_posts.size() - 1;
    //------------------
    for(int i = 0;i <= 12 && state_post_num >= 0;i++)
    {
        button[i]->setEnabled(true);
        button[i]->setText(game_posts[state_post_num--].title);
    }

    connect(bg,SIGNAL(buttonClicked(int)),this,SLOT(click_posts(int)));
    connect(push_post->ui->push, SIGNAL(clicked(bool)),this,SLOT(refresh()));
    connect(post_detail->ui->delete_this_post, SIGNAL(clicked(bool)),this,SLOT(refresh()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_game_clicked()
{
    page_post_num = 0;
    for(int i = 0;i <= 12;i++)
    {
        button[i]->setText("");
        button[i]->setEnabled(false);
    }
    state = game;
    QVector<Post> game_posts = all_post.value(state);
    state_post_num = game_posts.size() - 1;
    //------------------
    for(int i = 0;i <= 12 && state_post_num >= 0;i++)
    {
        button[i]->setEnabled(true);
        button[i]->setText(game_posts[state_post_num--].title);
    }
}

void MainWindow::on_movie_clicked()
{
    page_post_num = 0;
    state = movie;
    for(int i = 0;i <= 12;i++)
    {
        button[i]->setText("");
        button[i]->setEnabled(false);
    }
    QVector<Post> movie_posts = all_post.value(state);

    state_post_num = movie_posts.size() - 1;
    //------------------
    for(int i = 0;i <= 12 && state_post_num >= 0;i++)
    {
        button[i]->setEnabled(true);
        button[i]->setText(movie_posts[state_post_num--].title);
    }
}

void MainWindow::on_comic_clicked()
{
    page_post_num = 0;
    state = comic;
    for(int i = 0;i <= 12;i++)
    {
        button[i]->setText("");
        button[i]->setEnabled(false);
    }
    QVector<Post> comic_posts = all_post.value(state);
    state_post_num = comic_posts.size() - 1;
    //------------------
    for(int i = 0;i <= 12 && state_post_num >= 0;i++)
    {
        button[i]->setEnabled(true);
        button[i]->setText(comic_posts[state_post_num--].title);
    }
}

void MainWindow::on_music_clicked()
{
    page_post_num = 0;
    state = music;
    for(int i = 0;i <= 12;i++)
    {
        button[i]->setText("");
        button[i]->setEnabled(false);
    }
    QVector<Post> music_posts = all_post.value(state);
    state_post_num = music_posts.size() - 1;
    //------------------
    for(int i = 0;i <= 12 && state_post_num >= 0;i++)
    {
        button[i]->setEnabled(true);
        button[i]->setText(music_posts[state_post_num--].title);
    }
}

void MainWindow::on_sport_clicked()
{
    page_post_num = 0;
    state = sports;
    for(int i = 0;i <= 12;i++)
    {
        button[i]->setText("");
        button[i]->setEnabled(false);
    }
    QVector<Post> sports_posts = all_post.value(state);
    state_post_num = sports_posts.size() - 1;
    //------------------
    for(int i = 0;i <= 12 && state_post_num >= 0;i++)
    {
        button[i]->setEnabled(true);
        button[i]->setText(sports_posts[state_post_num--].title);
    }

}

void MainWindow::on_post_clicked()
{
    push_post->state = state;
    push_post->username = username;

    Post a;
    push_post->a = a;
    push_post->setWindowModality(Qt::ApplicationModal);
    push_post->setWindowTitle(QObject::tr("发帖"));
    push_post->show();
}

void MainWindow::on_next_page_clicked()
{
    QVector<Post> this_state_posts = all_post.value(state);
    if((page_post_num+1)*13 < this_state_posts.size())
    {
        for(int i = 0;i <= 12;i++)
        {
            button[i]->setText("");
            button[i]->setEnabled(false);
        }
        page_post_num++;
        state_post_num = this_state_posts.size() - 1 - 13*page_post_num;
        for(int i = 0;i <= 12 && state_post_num >= 0;i++)
        {
            button[i]->setEnabled(true);
            button[i]->setText(this_state_posts[state_post_num--].title);
        }
    }
}

void MainWindow::on_back_clicked()
{
    if(page_post_num-1>=0)
    {
        for(int i = 0;i <= 12;i++)
        {
            button[i]->setText("");
            button[i]->setEnabled(false);
        }
        page_post_num--;
        QVector<Post> this_state_posts = all_post.value(state);
        state_post_num = this_state_posts.size() - 1 - 13*page_post_num;
        for(int i = 0;i <= 12 && state_post_num >= 0;i++)
        {
            button[i]->setEnabled(true);
            button[i]->setText(this_state_posts[state_post_num--].title);
        }
    }
}

void MainWindow::refresh()
{
    page_post_num = 0;
    for(int i = 0;i <= 12;i++)
    {
        button[i]->setText("");
        button[i]->setEnabled(false);
    }
    QVector<Post> posts = all_post.value(state);

    state_post_num = posts.size() - 1;
    for(int i = 0;i <= 12 && state_post_num >= 0;i++)
    {
        button[i]->setEnabled(true);
        button[i]->setText(posts[state_post_num--].title);
    }
}

void MainWindow::click_posts(int i)
{
    QVector<Post> this_state_posts = all_post.value(state);
    int selected_post = this_state_posts.size() - 1 - 13*page_post_num -i;

    post_detail->p.title = this_state_posts[selected_post].title;
    post_detail->p.content = this_state_posts[selected_post].content;
    post_detail->p.comment = this_state_posts[selected_post].comment;
    post_detail->p.time = this_state_posts[selected_post].time;
    post_detail->p.poster_name = this_state_posts[selected_post].poster_name;
    post_detail->p.id = this_state_posts[selected_post].id;
    post_detail->p.state = this_state_posts[selected_post].state;
    post_detail->username = username;
    post_detail->level = level;
    post_detail->state = state;
    post_detail->responsible_plate = responsible_plate;
    post_detail->this_post_num = selected_post;
    post_detail->ui->title->setText(post_detail->p.title);
    post_detail->setWindowTitle(QObject::tr("帖子详情"));
    QString all_content;
//    qDebug() << "yonghuming" << post_detail->p.poster_name;
    all_content.append("用户:" + post_detail->p.poster_name+ "   发送时间:" + post_detail->p.time +"\n\n");
    all_content.append(post_detail->p.content+"\n\n");
    all_content.append("------------------------------------------\n\n");
    for(int i = 0; i <= post_detail->p.comment.size()-1;i++)
    {
        all_content.append("用户:" + post_detail->p.comment[i].username + "   发送时间:" + post_detail->p.comment[i].time +"\n\n");
        all_content.append(post_detail->p.comment[i].content+"\n\n");
        all_content.append("------------------------------------------\n\n");
    }
    post_detail->ui->content->setText(all_content);
    post_detail->setWindowModality(Qt::ApplicationModal);
    if(!(level == "administrator" || (level == "moderator" && state == responsible_plate) || (post_detail->p.poster_name == username && post_detail->p.comment.isEmpty())))
        post_detail->ui->delete_this_post->setEnabled(false);
    else
        post_detail->ui->delete_this_post->setEnabled(true);
    post_detail->show();
}
