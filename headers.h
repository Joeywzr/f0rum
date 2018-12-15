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
    int user_error = 0;

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
        QString line;
        QList<QString> strlist;
        bool flag = true;
        while(!fin.atEnd())
        {
            line = fin.readLine();
            strlist = line.split(" ");

            if(strlist.size() != 5)
                users.user_error++;
            else
            {
                users.id = strlist[0].toInt();
                if(users.id == 0)
                    flag = false;

                users.username = strlist[1];
                users.password = strlist[2];

                users.level = strlist[3];
                if(users.level != "administrator" && users.level != "ordinary" && users.level != "moderator")
                    flag = false;

                users.responsible_plate = strlist[4].toInt();
                if(users.responsible_plate < 0 || users.responsible_plate > 5)
                    flag = false;
                if(flag)
                    all_users.push_back(users);
                else
                {
                    users.user_error++;
                    flag = true;
                }
            }
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
