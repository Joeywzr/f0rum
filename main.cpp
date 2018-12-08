#include "loginwindow.h"
#include "post.h"
#include "user.h"
#include <QApplication>
#include <QFile>
#include <administrators.h>
#include <QSqlQuery>
#include <QDebug>
Comment com;
QHash<Category,QVector<Post>> all_post;//所有帖子
QVector<user_variable> all_users;//所有用户
int max_id;//最大用户id
void database_init();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginWindow w;//登录界面
    w.show();

    return a.exec();
}
