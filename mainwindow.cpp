#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(QObject::tr("C++“学习”论坛"));
    qDebug() << "user_num:"<<all_users.size();
    //--------帖子列表显示设置---------------------
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
    for(int i = 0;i <= 12; i++)
    {
        button[i]->setStyleSheet("QPushButton{text-align : left;"
                                 "border:none;"
                                 "color:blue;"
                                 "font-weight: bold;}");
        button[i]->setEnabled(false);
        button[i]->setText("");
    }
    bg = new QButtonGroup;
    post_detail = new Details_of_posts(this);
    for(int i = 0;i <= 12;i++)
        bg->addButton(button[i],i);
    //-----------------------------------

    //---默认初始板块为game-------
    state = game;
    page_post_num = 0;
    QVector<Post> game_posts = all_post.value(state);
    state_post_num = game_posts.size() - 1;
    ui->game->setChecked(true);
    ui->game->setCheckable(true);
    ui->game->setAutoExclusive(true);
    for(int i = 0;i <= 12 && state_post_num >= 0;i++)
    {
        button[i]->setEnabled(true);
        button[i]->setText(game_posts[state_post_num--].title);
    }
    //-----------------------------------

    connect(bg,SIGNAL(buttonClicked(int)),this,SLOT(click_posts(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_game_clicked()//点击游戏板块
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
    for(int i = 0;i <= 12 && state_post_num >= 0;i++)
    {
        button[i]->setEnabled(true);
        button[i]->setText(game_posts[state_post_num--].title);
    }
}

void MainWindow::on_movie_clicked()//点击电影板块
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
    for(int i = 0;i <= 12 && state_post_num >= 0;i++)
    {
        button[i]->setEnabled(true);
        button[i]->setText(movie_posts[state_post_num--].title);
    }
}

void MainWindow::on_comic_clicked()//点击动漫板块
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
    for(int i = 0;i <= 12 && state_post_num >= 0;i++)
    {
        button[i]->setEnabled(true);
        button[i]->setText(comic_posts[state_post_num--].title);
    }
}

void MainWindow::on_music_clicked()//点击音乐板块
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
    for(int i = 0;i <= 12 && state_post_num >= 0;i++)
    {
        button[i]->setEnabled(true);
        button[i]->setText(music_posts[state_post_num--].title);
    }
}

void MainWindow::on_sport_clicked()//点击体育板块
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
    for(int i = 0;i <= 12 && state_post_num >= 0;i++)
    {
        button[i]->setEnabled(true);
        button[i]->setText(sports_posts[state_post_num--].title);
    }

}

void MainWindow::on_next_page_clicked()//点击下一页
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

void MainWindow::on_back_clicked()//点击上一页
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


void MainWindow::click_posts(int i)//点击帖子
{
    QVector<Post> this_state_posts = all_post.value(state);
    int selected_post = this_state_posts.size() - 1 - 13*page_post_num -i;
    //帖子详情初始化
    post_detail->p.title = this_state_posts[selected_post].title;
    post_detail->p.content = this_state_posts[selected_post].content;
    post_detail->p.comment = this_state_posts[selected_post].comment;
    post_detail->p.comment_num = this_state_posts[selected_post].comment_num;
    post_detail->p.time = this_state_posts[selected_post].time;
    post_detail->p.poster_name = this_state_posts[selected_post].poster_name;
    post_detail->p.id = this_state_posts[selected_post].id;
    post_detail->p.state = this_state_posts[selected_post].state;
    post_detail->username = username;
    post_detail->id = id;
    post_detail->level = level;
    post_detail->state = state;
    post_detail->responsible_plate = responsible_plate;
    post_detail->this_post_num = selected_post;
    post_detail->ui->title->setText(post_detail->p.title);
    post_detail->setWindowTitle(QObject::tr("帖子详情"));
    //帖子内容显示
    QString all_content;
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
    //判断各个按钮能否使用
    if(id < 0)
    {
        post_detail->ui->comment->setEnabled(false);
        post_detail->ui->comment_edit->setEnabled(false);
        post_detail->ui->delete_this_post->setEnabled(false);
    }
    if(!(level == "administrator" || (level == "moderator" && state == responsible_plate) || (post_detail->p.poster_name == username && post_detail->p.comment.isEmpty())))
        post_detail->ui->delete_this_post->setEnabled(false);
    else
        post_detail->ui->delete_this_post->setEnabled(true);
    post_detail->show();
}

void MainWindow::closeEvent(QCloseEvent *event)//点击右上角退出
{
    if(id > 0)
    {
        QFile user("user.txt");
        QFile post("post.txt");

        user.open( QFile::ReadWrite | QFile :: Truncate );
        QTextStream fout1(&user);
        user_variable users;
        fout1 << users;
        user.close();

        post.open( QFile::ReadWrite | QFile :: Truncate );
        QTextStream fout2(&post);
        Post posts;
        fout2 << posts;
        post.close();
    }
    all_users.clear();
    all_post.clear();
    event->accept();
}
