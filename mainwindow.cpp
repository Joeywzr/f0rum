#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(QObject::tr("C++学习论坛"));
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
    connect(bg,SIGNAL(buttonClicked(int)),this,SLOT(click_posts(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::get_post_from_server(QString str, QVector<Post> &this_state_posts, Post posts)
{
    QList<QString> list1, list2;
    QList<QString>::iterator i;
    bool flag = true;
    list1 = str.split(" ### ");//按" ### "分隔读取各个帖子
    if(list1.size() <= 1)
        return;
    for(i = list1.begin();i != list1.end();i++)
    {
        list2 = (*i).split(" $$$ ");//按" $$$ "分隔读取帖子内部信息
        if(list2.size() != 7 + list2[4].toInt()*3)//如果帖子内部信息数量不对应
            posts.post_error++;
        else
        {
            for(int ii = 0;ii < list2.size();ii++)
                if(list2[ii].size() == 0)
                    flag = false;
            posts.state = list2[0];
            if(posts.state != "novice" &&posts.state != "technology" &&posts.state != "resources" &&posts.state != "relax" && posts.state != "appeal")
                flag = false;
            posts.id = list2[1].toInt();
            posts.poster_name = list2[2];
            posts.time = list2[3];
            posts.comment_num = list2[4].toInt();
            posts.title = list2[5];
            posts.content = list2[6];
            //读取评论信息
            for(int j = 7;j < list2.size();j++)
            {
                if(j % 3 == 1)
                    com.username = list2[j];
                else if(j % 3 == 2)
                    com.time = list2[j];
                else if(j % 3 == 0)
                {
                    com.content = list2[j];
                    posts.comment.push_back(com);
                }
            }
            if(flag)//如果没错误就读入该帖子信息
                this_state_posts.push_back(posts);
            else//若帖子有错则跳过该帖子不读入
            {
                posts.post_error++;
                flag = true;
            }
            posts.comment.clear();
        }
    }
}

void MainWindow::on_novice_clicked()//点击游戏板块
{
    QString ss = "novice";
    tcpsocket->write(ss.toStdString().c_str(),strlen(ss.toStdString().c_str()));
    tcpsocket->waitForReadyRead();
    QTextStream in(tcpsocket);
    ss = in.readAll();
    qDebug()<< ss;

    page_post_num = 0;
    for(int i = 0;i <= 12;i++)
    {
        button[i]->setText("");
        button[i]->setEnabled(false);
    }
    state = novice;
    if(ss == "None")
        return;

    QVector<Post> novice_posts;
    Post posts;
    get_post_from_server(ss,novice_posts,posts);
    state_post_num = novice_posts.size() - 1;
    qDebug()<< state_post_num;
    for(int i = 0;i <= 12 && state_post_num >= 0;i++)
    {
        button[i]->setEnabled(true);
        button[i]->setText(novice_posts[state_post_num--].title);
    }
}

void MainWindow::on_technology_clicked()//点击电影板块
{
    QString ss = "technology";
    tcpsocket->write(ss.toStdString().c_str(),strlen(ss.toStdString().c_str()));
    tcpsocket->waitForReadyRead();
    QTextStream in(tcpsocket);
    ss = in.readAll();
    qDebug()<< ss;

    page_post_num = 0;
    for(int i = 0;i <= 12;i++)
    {
        button[i]->setText("");
        button[i]->setEnabled(false);
    }
    state = technology;
    if(ss == "None")
        return;
    QVector<Post> technology_posts;
    Post posts;
    get_post_from_server(ss,technology_posts,posts);
    state_post_num = technology_posts.size() - 1;
    for(int i = 0;i <= 12 && state_post_num >= 0;i++)
    {
        button[i]->setEnabled(true);
        button[i]->setText(technology_posts[state_post_num--].title);
    }
}

void MainWindow::on_resources_clicked()//点击动漫板块
{
    QString ss = "resources";
    tcpsocket->write(ss.toStdString().c_str(),strlen(ss.toStdString().c_str()));
    tcpsocket->waitForReadyRead();
    QTextStream in(tcpsocket);
    ss = in.readAll();
    qDebug()<< ss;

    page_post_num = 0;
    for(int i = 0;i <= 12;i++)
    {
        button[i]->setText("");
        button[i]->setEnabled(false);
    }
    state = resources;
    if(ss == "None")
        return;
    QVector<Post> resources_posts;
    Post posts;
    get_post_from_server(ss,resources_posts,posts);
    state_post_num = resources_posts.size() - 1;
    for(int i = 0;i <= 12 && state_post_num >= 0;i++)
    {
        button[i]->setEnabled(true);
        button[i]->setText(resources_posts[state_post_num--].title);
    }
}

void MainWindow::on_relax_clicked()//点击音乐板块
{
    QString ss = "relax";
    tcpsocket->write(ss.toStdString().c_str(),strlen(ss.toStdString().c_str()));
    tcpsocket->waitForReadyRead();
    QTextStream in(tcpsocket);
    ss = in.readAll();
    qDebug()<< ss;

    page_post_num = 0;
    for(int i = 0;i <= 12;i++)
    {
        button[i]->setText("");
        button[i]->setEnabled(false);
    }
    state = relax;
    if(ss == "None")
        return;
    QVector<Post> relax_posts;
    Post posts;
    get_post_from_server(ss,relax_posts,posts);
    state_post_num = relax_posts.size() - 1;
    for(int i = 0;i <= 12 && state_post_num >= 0;i++)
    {
        button[i]->setEnabled(true);
        button[i]->setText(relax_posts[state_post_num--].title);
    }
}

void MainWindow::on_appeal_clicked()//点击体育板块
{
    QString ss = "appeal";
    tcpsocket->write(ss.toStdString().c_str(),strlen(ss.toStdString().c_str()));
    tcpsocket->waitForReadyRead();
    QTextStream in(tcpsocket);
    ss = in.readAll();
    qDebug()<< ss;

    page_post_num = 0;
    for(int i = 0;i <= 12;i++)
    {
        button[i]->setText("");
        button[i]->setEnabled(false);
    }
    state = appeal;
    if(ss == "None")
        return;
    QVector<Post> appeal_posts;
    Post posts;
    get_post_from_server(ss,appeal_posts,posts);
    state_post_num = appeal_posts.size() - 1;
    for(int i = 0;i <= 12 && state_post_num >= 0;i++)
    {
        button[i]->setEnabled(true);
        button[i]->setText(appeal_posts[state_post_num--].title);
    }

}

void MainWindow::on_next_page_clicked()//点击下一页
{
    QString ss;
    if(state == novice)
        ss = "novice";
    else if(state == technology)
        ss = "technology";
    else if(state == resources)
        ss = "resources";
    else if(state == relax)
        ss = "relax";
    else if(state == appeal)
        ss = "appeal";
    tcpsocket->write(ss.toStdString().c_str(),strlen(ss.toStdString().c_str()));
    tcpsocket->waitForReadyRead();
    QTextStream in(tcpsocket);
    ss = in.readAll();

    QVector<Post> this_state_posts;
    Post posts;
    get_post_from_server(ss,this_state_posts,posts);
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
    QString ss;
    if(state == novice)
        ss = "novice";
    else if(state == technology)
        ss = "technology";
    else if(state == resources)
        ss = "resources";
    else if(state == relax)
        ss = "relax";
    else if(state == appeal)
        ss = "appeal";
    tcpsocket->write(ss.toStdString().c_str(),strlen(ss.toStdString().c_str()));
    tcpsocket->waitForReadyRead();
    QTextStream in(tcpsocket);
    ss = in.readAll();
    if(page_post_num-1>=0)
    {
        for(int i = 0;i <= 12;i++)
        {
            button[i]->setText("");
            button[i]->setEnabled(false);
        }
        page_post_num--;
        QVector<Post> this_state_posts;
        Post posts;
        get_post_from_server(ss,this_state_posts,posts);
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
    QString ss;
    if(state == novice)
        ss = "novice";
    else if(state == technology)
        ss = "technology";
    else if(state == resources)
        ss = "resources";
    else if(state == relax)
        ss = "relax";
    else if(state == appeal)
        ss = "appeal";
    tcpsocket->write(ss.toStdString().c_str(),strlen(ss.toStdString().c_str()));
    tcpsocket->waitForReadyRead();
    QTextStream in(tcpsocket);
    ss = in.readAll();
    QVector<Post> this_state_posts;
    Post posts;
    get_post_from_server(ss,this_state_posts,posts);

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
    this->close();
    tcpsocket->abort();
    event->accept();
}
