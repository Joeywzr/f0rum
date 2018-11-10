#include "mainwindow.h"
#include "loginwindow.h"
#include "registered_user.h"
#include <QApplication>
#include <QFile>
#include <administrators.h>
#include <QSqlQuery>
QSqlDatabase database;
QSqlQuery sql_query;
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
        QString select_sql = "select id, name from registered_user";
        if(!sql_query.exec(select_sql))
        {
            QString create_sql = "create table registered_user (id int , username QString, password QString)";
            sql_query.prepare(create_sql);
            if(!sql_query.exec())
            {
                qDebug() << "Error: Fail to create table." << sql_query.lastError();
            }
            else
            {
                qDebug() << "Table created!";
            }
        }
    }
    QString select_max_sql = "select max(id) from registered_user";
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





//------------qss美化--------------------
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
