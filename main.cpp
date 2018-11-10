#include "mainwindow.h"
#include "loginwindow.h"
#include "registered_user.h"
#include <QApplication>
#include <QFile>
#include <administrators.h>
QSqlDatabase database;

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

    database.close();
    return a.exec();
}
