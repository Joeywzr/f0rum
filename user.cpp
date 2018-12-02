#include "user.h"

User::User(QObject *parent) : QObject(parent)
{

}


bool User::sign_in(QString username_input, QString password_input, bool &username_flag, int &id, QString &level, int &responsible_plate)
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
