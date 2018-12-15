#include "moderatorwindow.h"
#include "ui_moderatorwindow.h"

Moderatorwindow::Moderatorwindow(Category s, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Moderatorwindow)
{
    ui->setupUi(this);
    state = s;//当前板块
    //-----------界面初始化
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
    user_num = all_users.size() - 1;
    for(int i = 0;i <= 12 && user_num >= 0 && all_users[user_num].level != "administrator";i++)
    {
        button[i]->setEnabled(true);
        button[i]->setText(all_users[user_num].username);
        if(all_users[user_num].level == "moderator" && all_users[user_num].responsible_plate == state)
        {
            button[i]->setCheckState(Qt::Checked);
        }
        user_num--;
    }
    //----------------------------------------------
    connect(bg,SIGNAL(buttonClicked(int)),this,SLOT(click_users(int)));
}

void Moderatorwindow::click_users(int i )//点击用户名
{
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
    }
    else if(button[i]->checkState() == Qt::Checked && all_users[temp].level == "moderator" && all_users[temp].responsible_plate != state)
    {
        QMessageBox::StandardButton button1;
        button1 = QMessageBox::question(this, tr("警告"),QString(tr("此操作将取消该用户在其他版的版主身份，是否继续?")),QMessageBox::Yes | QMessageBox::No);
        if (button1 == QMessageBox::No)
            button[i]->setCheckState(Qt::Unchecked);
        else if (button1 == QMessageBox::Yes)
        {
           button[i]->setCheckState(Qt::Checked);
           all_users[temp].responsible_plate = state;
        }
    }
}

void Moderatorwindow::on_next_page_clicked()//点击下一页
{
    if((page_num+1)*13 < all_users.size())
    {
        for(int i = 0;i <= 12;i++)
        {
            button[i]->setText("");
            button[i]->setEnabled(false);
            button[i]->setCheckState(Qt::Unchecked);
        }
        page_num++;
        user_num = all_users.size() - 1 - 13*page_num;
        for(int i = 0;i <= 12 && user_num >= 0 && all_users[user_num].level != "administrator";i++)
        {
            button[i]->setEnabled(true);
            button[i]->setText(all_users[user_num].username);
            if(all_users[user_num].level == "moderator" && all_users[user_num].responsible_plate == state)
                button[i]->setCheckState(Qt::Checked);
            user_num--;
        }
    }
}

void Moderatorwindow::on_back_clicked()//点击上一页
{
    if(page_num-1>=0)
    {
        for(int i = 0;i <= 12;i++)
        {
            button[i]->setText("");
            button[i]->setEnabled(false);
            button[i]->setCheckState(Qt::Unchecked);
        }
        page_num--;
        user_num = all_users.size() -1 - 13*page_num;
        for(int i = 0;i <= 12 && user_num >= 0 && all_users[user_num].level != "administrator";i++)
        {
            qDebug()<< all_users[user_num].username << all_users[user_num].level << all_users[user_num].responsible_plate;
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

void Moderatorwindow::on_quit_clicked()//点击关闭
{
    this->close();
}
