#include "mainwindow.h"
#include "loginwindow.h"
#include "ordinary_user.h"
#include "post.h"
#include "user.h"
#include <QApplication>
#include <QFile>
#include <administrators.h>
#include <QSqlQuery>
#include <QDebug>

QSqlDatabase database;
QHash<Category,QVector<Post>> all_post;
QVector<user_variable> all_users;
int max_id;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

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

//-------------------------------------------------------------
//------------qss美化------------------------------------------
//    QFile qss(":/qss/style.qss");
//    if(qss.open(QFile::ReadOnly))
//    {
//        qDebug("open success");
//        QString style = QLatin1String(qss.readAll());
//        a.setStyleSheet(style);
//        qss.close();
//    }
//    else
//    {
//        qDebug("open failed");
//    }
//---------------------------------------

    LoginWindow w;
    w.show();

    return a.exec();

}
