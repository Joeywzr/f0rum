#include "user.h"

User::User(QObject *parent) : QObject(parent)
{

}

void User::init_class()
{
    mainview = new MainWindow;
    mainview->username = username;
    mainview->password = password;
    mainview->level = level;
    mainview->id = id;
    mainview->show();
    connect(mainview->ui->personal_infomation,SIGNAL(clicked(bool)), this, SLOT(user_information()));
    connect(mainview->ui->sign_out,SIGNAL(clicked(bool)), this, SLOT(sign_out()));
    connect(mainview->ui->appoint, SIGNAL(clicked(bool)),this,SLOT(appoint_or_revoke_moderator()));
    connect(mainview->ui->post, SIGNAL(clicked(bool)),this,SLOT(push_post()));
    connect(mainview->post_detail->ui->delete_this_post, SIGNAL(clicked(bool)),this,SLOT(refresh()));
}

void User::push_post()
{
    writepost = new Writepostwindow;
    writepost->state = mainview->state;
    writepost->username = username;
    Post a;
    writepost->a = a;
    writepost->setWindowModality(Qt::ApplicationModal);
    writepost->setWindowTitle(QObject::tr("发帖"));
    connect(writepost->ui->push, SIGNAL(clicked(bool)), this, SLOT(refresh()));
    writepost->show();
}

void User::refresh()
{
    mainview->page_post_num = 0;
    for(int i = 0;i <= 12;i++)
    {
        mainview->button[i]->setText("");
        mainview->button[i]->setEnabled(false);
    }
    QVector<Post> posts = all_post.value(mainview->state);

    mainview->state_post_num = posts.size() - 1;
    for(int i = 0;i <= 12 && mainview->state_post_num >= 0;i++)
    {
        mainview->button[i]->setEnabled(true);
        mainview->button[i]->setText(posts[mainview->state_post_num--].title);
    }
}

void User::sign_out()
{
//    if (!database.open())
//    {
//        qDebug() << "Error: Failed to connect database." << database.lastError();
//    }
//    QSqlQuery sql_query;
//    QString clear_sql = "delete from users";
//    QString insert_sql = "insert into users values (?, ?, ?, ?, ?)";

//    sql_query.prepare(clear_sql);
//    if(!sql_query.exec())
//    {
//        qDebug() << sql_query.lastError();
//    }
//    else
//    {
//        //qDebug() << "table cleared user";
//    }

//    for(int i = 0;i < all_users.size();i++)
//    {
//        sql_query.prepare(insert_sql);
//        sql_query.addBindValue(all_users[i].id);
//        sql_query.addBindValue(all_users[i].username);
//        sql_query.addBindValue(all_users[i].password);
//        sql_query.addBindValue(all_users[i].level);
//        sql_query.addBindValue(all_users[i].responsible_plate);
//        if(!sql_query.exec())
//            qDebug() << sql_query.lastError();
//    }
//    all_users.clear();
    mainview->close();
}

bool User::sign_in(QString username_input, QString password_input,
                   bool &username_flag, int &id, QString &level,
                   int &responsible_plate)
{
    if (!database.open())
        qDebug() << "Error: Failed to connect database." << database.lastError();

    QString select_sql = "select id, username,password, level, responsible_plate from users";
    if(!sql_query.exec(select_sql))
        qDebug()<<sql_query.lastError();
    else
    {
        while(sql_query.next())
        {
            QString username = sql_query.value(1).toString();
            QString password = sql_query.value(2).toString();
            if(username_input == username)
            {
                username_flag = true;
                if(password_input == password)
                {
                    level = sql_query.value(3).toString();
                    responsible_plate = sql_query.value(4).toInt();
                    id = sql_query.value(0).toInt();
                    return true;
                }
                return false;
            }
        }
    }
    return false;
}

