#include "loginwindow.h"
#include "post.h"
#include "user.h"
#include <QApplication>
#include <QFile>
#include <administrators.h>
#include <QSqlQuery>
#include <QDebug>

QSqlDatabase database;//数据库
QHash<Category,QVector<Post>> all_post;//所有帖子
QVector<user_variable> all_users;//所有用户
int max_id;//最大用户id
void database_init();



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    database_init();//数据库初始化
    LoginWindow w;//登录界面
    w.show();

    return a.exec();
}

void database_init()//数据库初始化
{
    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        database = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        database = QSqlDatabase::addDatabase("QSQLITE");
        database.setDatabaseName("MyDataBase.db");
        database.setUserName("wzr");
        database.setPassword("123456");
    }
    QSqlQuery sql_query;
    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." << database.lastError();
    }
    else
    {
        QString users_sql = "select id, username from users";
        QString game_post_sql = "select id from game";
        QString movie_post_sql = "select id from movie";
        QString comic_post_sql = "select id from comic";
        QString music_post_sql = "select id from music";
        QString sports_post_sql = "select id from sports";
        if(!sql_query.exec(users_sql))
        {
            QString create_sql = "create table users (id int, username QString, password QString, level QString, responsible_plate int)";
            sql_query.prepare(create_sql);
            if(!sql_query.exec())
                qDebug() << "Error: Fail to create table." << sql_query.lastError();
            else
                qDebug() << "Table created!";
        }
        if(!sql_query.exec(game_post_sql))
        {
            QString create_sql = "create table game (id int , poster_name QString, title QString, content QString, time QString)";
            sql_query.prepare(create_sql);
            if(!sql_query.exec())
                qDebug() << "Error: Fail to create table." << sql_query.lastError();
            else
                qDebug() << "Table created!";
        }
        if(!sql_query.exec(movie_post_sql))
        {
            QString create_sql = "create table movie (id int , poster_name QString, title QString, content QString, time QString)";
            sql_query.prepare(create_sql);
            if(!sql_query.exec())
                qDebug() << "Error: Fail to create table." << sql_query.lastError();
            else
                qDebug() << "Table created!";
        }
        if(!sql_query.exec(comic_post_sql))
        {
            QString create_sql = "create table comic (id int , poster_name QString, title QString, content QString, time QString)";
            sql_query.prepare(create_sql);
            if(!sql_query.exec())
                qDebug() << "Error: Fail to create table." << sql_query.lastError();
            else
                qDebug() << "Table created!";
        }
        if(!sql_query.exec(music_post_sql))
        {
            QString create_sql = "create table music (id int , poster_name QString, title QString, content QString, time QString)";
            sql_query.prepare(create_sql);
            if(!sql_query.exec())
                qDebug() << "Error: Fail to create table." << sql_query.lastError();
            else
                qDebug() << "Table created!";
        }
        if(!sql_query.exec(sports_post_sql))
        {
            QString create_sql = "create table sports (id int , poster_name QString, title QString, content QString, time QString)";
            sql_query.prepare(create_sql);
            if(!sql_query.exec())
                qDebug() << "Error: Fail to create table." << sql_query.lastError();
            else
                qDebug() << "Table created!";
        }
    }
    QString select_max_sql = "select max(id) from users";
    sql_query.prepare(select_max_sql);
    if(!sql_query.exec())
    {
        qDebug() << sql_query.lastError();
    }
    else
    {
        while(sql_query.next())
            max_id = sql_query.value(0).toInt();
        max_id++;
        qDebug() << QString("max id:%1").arg(max_id);
    }
    //初始配置
    QVector<Post> p_vec;
    Post p1, p2;
    Comment c1, c2;

    c1.content = "我是一楼";
    c1.time = "2018-12-04:12:36:24";
    c1.username = "ad1";
    c2.content = "我是二楼";
    c2.time = "2018-12-04:13:46:56";
    c2.username = "ad1";

    p1.poster_name = "ad1";
    p1.time = "2018-12-04:12:35:45";
    p1.title = "for test1";
    p1.content = "text";
    p1.comment.append(c1);
    p1.comment.append(c2);

    p2.poster_name = "ad1";
    p2.time = "2018-12-04:13:45:15";
    p2.title = "for test2";
    p2.content = "text";
    p2.comment.append(c1);
    p2.comment.append(c2);

    p_vec.append(p1);
    p_vec.append(p2);

    p_vec[0].state = "game";
    p_vec[1].state = "game";
    all_post[game] = p_vec;
    p_vec[0].state = "movie";
    p_vec[1].state = "movie";
    all_post[movie] = p_vec;
    p_vec[0].state = "comic";
    p_vec[1].state = "comic";
    all_post[comic] = p_vec;
    p_vec[0].state = "music";
    p_vec[1].state = "music";
    all_post[music] = p_vec;
    p_vec[0].state = "sports";
    p_vec[1].state = "sports";
    all_post[sports] = p_vec;
}
