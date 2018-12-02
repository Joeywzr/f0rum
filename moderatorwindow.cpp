#include "moderatorwindow.h"
#include "ui_moderatorwindow.h"

Moderatorwindow::Moderatorwindow(Category s, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Moderatorwindow)
{
    ui->setupUi(this);
    state = s;
    button[0] = ui->checkBox_1;
    button[1] = ui->checkBox_2;
    button[2] = ui->checkBox_3;
    button[3] = ui->checkBox_4;
    button[4] = ui->checkBox_5;
    button[5] = ui->checkBox_6;
    button[6] = ui->checkBox_7;
    button[7] = ui->checkBox_8;
    button[8] = ui->checkBox_9;
    button[9] = ui->checkBox_10;
    button[10] = ui->checkBox_11;
    button[11] = ui->checkBox_12;
    button[12] = ui->checkBox_13;

    page_num = 0;
    for(int i = 0;i < 13; i++)
    {
        button[i]->setStyleSheet("border:none;");
        button[i]->setEnabled(false);
    }

    bg = new QButtonGroup;
    for(int i = 0;i <= 12;i++)
        bg->addButton(button[i],i);
    bg->setExclusive(false);
    user_num = all_users.size()-1;
    //qDebug()<<"到这还没错" << all_users.size();
    //------------------
    for(int i = 0;i <= 12 && user_num >= 5;i++)
    {
        button[i]->setEnabled(true);
        button[i]->setText(all_users[user_num].username);

        if(all_users[user_num].level == "moderator" && all_users[user_num].responsible_plate == state)
        {
            button[i]->setCheckState(Qt::Checked);
            qDebug()<<"对勾";
        }
        user_num--;
    }
    connect(bg,SIGNAL(buttonToggled(int,bool)),this,SLOT(click_users(int)));
}

void Moderatorwindow::click_users(int i )
{
    //qDebug()<<"跑到这啦";
    int temp = all_users.size() - 1 - 13*page_num - i;
    if(button[i]->checkState() == Qt::Unchecked)
    {
        all_users[temp].level = "ordinary";
        all_users[temp].responsible_plate = 0;
    }
    else if(button[i]->checkState() == Qt::Checked && all_users[temp].level == "ordinary")
    {

        all_users[temp].level = "moderator";
        all_users[temp].responsible_plate = state;
        qDebug()<< all_users[temp].id << all_users[temp].level << all_users[temp].responsible_plate;
    }
    else if(button[i]->checkState() == Qt::Checked && all_users[temp].level == "moderator" && all_users[temp].responsible_plate != state)
    {
        all_users[temp].responsible_plate = state;
    }
}

void Moderatorwindow::on_next_page_clicked()
{
    if((page_num+1)*13 < (all_users.size() - 5))
    {
        for(int i = 0;i <= 12;i++)
        {
            button[i]->setText("");
            button[i]->setEnabled(false);
        }
        page_num++;
        user_num = all_users.size() - 1 - 13*page_num;
        for(int i = 0;i <= 12 && user_num >= 5;i++)
        {
            button[i]->setEnabled(true);
            button[i]->setText(all_users[user_num].username);
            if(all_users[user_num].level == "moderator" && all_users[user_num].responsible_plate == state)
                button[i]->setCheckState(Qt::Checked);
            user_num--;
        }
    }
}

void Moderatorwindow::on_back_clicked()
{
    if(page_num-1>=0)
    {
        for(int i = 0;i <= 12;i++)
        {
            button[i]->setText("");
            button[i]->setEnabled(false);
        }
        page_num--;
        user_num = all_users.size() -1 - 13*page_num;
        for(int i = 0;i <= 12 && user_num >= 5;i++)
        {
            button[i]->setEnabled(true);
            button[i]->setText(all_users[user_num].username);
            if(all_users[user_num].level == "moderator" && all_users[user_num].responsible_plate == state)
                button[i]->setCheckState(Qt::Checked);
            user_num--;
        }
    }
}

Moderatorwindow::~Moderatorwindow()
{
    delete ui;
}

