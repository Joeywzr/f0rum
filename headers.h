#ifndef HEADERS_H
#define HEADERS_H
#include <QObject>
#include <QDebug>
#include <QWidget>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include <QVector>
#include <QMainWindow>
#include <QMessageBox>
#include <QCloseEvent>
#include <QDate>
#include <QTime>
#include <QList>
#include <QDateTime>
#include <QCloseEvent>
#include <QLabel>
#include <QButtonGroup>
#include <QCheckBox>
#include <QDataStream>
#include <QDialog>
#include <QRegExpValidator>
#include <ostream>
#include <istream>
#include <iostream>
#include <sstream>
#include <fstream>
class user_variable;
extern QVector<user_variable> all_users;//所有用户
class user_variable
{
public:
    int id;
    QString username;
    QString password;
    QString level;
    int responsible_plate;

    friend QTextStream& operator << (QTextStream &fout, user_variable &users)
    {
        for(int i = 0;i < all_users.size();i++)
        {
            users = all_users[i];
            fout << QString::number(users.id) << " ";
            fout << users.username << " ";
            fout << users.password << " ";
            fout << users.level << " ";
            fout << users.responsible_plate << endl;
        }
        return fout;
    }
    friend QTextStream& operator >> (QTextStream &fin, user_variable &users)
    {
        QString str;
        while((fin >> str).status() == QTextStream::Ok)
        {
            users.id = str.toInt();
            fin >> str;
            users.username = str;
            fin >> str;
            users.password = str;
            fin >> str;
            users.level = str;
            fin >> str;
            users.responsible_plate = str.toInt();
            all_users.push_back(users);
        }
        return fin;
    }
};
typedef enum
{
    game=1,
    movie,
    comic,
    music,
    sports
}Category;

#endif // HEADERS_H
