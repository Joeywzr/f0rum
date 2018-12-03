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
#include <QDateTime>
#include <QCloseEvent>
#include <QLabel>
#include <QButtonGroup>
#include <QCheckBox>
#include <QDialog>
typedef struct USER_VAR
{
    int id;
    QString username;
    QString password;
    QString level;
    int responsible_plate;
}user_variable;
typedef enum
{
    game=1,
    movie,
    comic,
    music,
    sports
}Category;

#endif // HEADERS_H
