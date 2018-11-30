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

    Registered_user *register_user = new Registered_user;
    Administrators *administrators = new Administrators;
    bg = new QButtonGroup;
    for(int i = 0;i <= 12;i++)
        bg->addButton(button[i],i);
    if(id < 5)//管理员
    {
        administrators->info.id = id;
        administrators->info.username = username;
        administrators->info.password = password;
    }
    else//普通用户
    {
        register_user->info.id = id;
        register_user->info.username = username;
        register_user->info.password = password;
    }

    state = game;
    for(int i = game; i <= sports;i++)
    {
        QVector<Post> post;
        all_post.insert(state, post);
    }

    connect(bg,SIGNAL(buttonClicked(int)),this,SLOT(click_posts(int)));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_personal_infomation_clicked()
{
    per_info = new Personal_infomation(this);
    per_info->username = username;
    per_info->password = password;
    per_info->id = id;
    per_info->show_infomation();
    per_info->setModal(true);
    per_info->setWindowTitle(QObject::tr("发帖"));
    per_info->show();
}

void MainWindow::on_sign_out_clicked()
{
    this->close();
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
//    QVector<Post>::iterator i;



    //----从数据库中读取数据
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
//    QVector<Post>::iterator i;

    //----从数据库中读取数据

    //------------------
    state_post_num = movie_posts.size() - 1;
    //------------------
    for(int i = 0;i <= 12 && state_post_num >= 0;i++)
    {
        button[i]->setEnabled(true);
        button[i]->setText(movie_posts[state_post_num--].title);
    }
//    QWidget * widget = new QWidget();
//        widget->setWindowTitle(QObject::tr("I'm widget"));
//        QLabel * label = new QLabel();
//        label->setWindowTitle(QObject::tr("I'm label"));
//        label->setText(QObject::tr("label:I'm a window"));
//        label->resize(180,20);
//        QLabel * label2 = new QLabel(widget);
//        label2->setText(QObject::tr("label2:I'm not a dulideWindow,but window's son"));
//        label2->resize(250,20);
//        label->show();
//        widget->show();

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
//    QVector<Post>::iterator i;

    //----从数据库中读取数据

    //------------------
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
//    QVector<Post>::iterator i;

    //----从数据库中读取数据

    //------------------
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
//    QVector<Post>::iterator i;

    //----从数据库中读取数据

    //------------------
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
    push_post = new Writepostwindow(this);
    push_post->state = state;
    push_post->username = username;
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

void MainWindow::click_posts(int i)
{
    QVector<Post> this_state_posts = all_post.value(state);
    int selected_post = this_state_posts.size() - 1 - 13*page_post_num -i;

    post_detail = new Details_of_posts(this);
    post_detail->p.title = this_state_posts[selected_post].title;
    post_detail->p.content = this_state_posts[selected_post].content;
    post_detail->p.comment = this_state_posts[selected_post].comment;
    post_detail->p.time = this_state_posts[selected_post].time;
    post_detail->p.poster_name = this_state_posts[selected_post].poster_name;
    post_detail->username = username;
    post_detail->state = state;
    post_detail->this_post_num = selected_post;
    post_detail->ui->title->setText(post_detail->p.title);
    QString all_content;
    all_content.append("用户:");
    all_content.append(post_detail->p.poster_name+"\n\n");
    all_content.append(post_detail->p.content+"\n\n");
    all_content.append("------------------------------------------\n\n");
    for(int i = 0; i <= post_detail->p.comment.size() - 1;i++)
    {
        all_content.append("用户:");
        all_content.append(post_detail->p.comment[i].username+"\n\n");
        all_content.append(post_detail->p.comment[i].content+"\n\n");
        all_content.append("------------------------------------------\n\n");
    }

    post_detail->ui->content->setText(all_content);

    post_detail->show();

}
