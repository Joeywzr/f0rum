#include "administrators.h"

Administrators::Administrators()
{

}

void Administrators::init_class()
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
}

void Administrators::user_information()
{
    per_info = new Personal_infomation;
    per_info->username = username;
    per_info->id = id;
    per_info->level = level;
    per_info->show_respresponsible_plate = false;
    per_info->show_infomation();
    per_info->setModal(true);
    per_info->setWindowTitle(QObject::tr("个人信息"));
    per_info->show();
}

void Administrators::sign_out()
{
    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." << database.lastError();
    }
    QSqlQuery sql_query;
    QString clear_sql = "delete from users";
    QString insert_sql = "insert into users values (?, ?, ?, ?, ?)";

    sql_query.prepare(clear_sql);
    if(!sql_query.exec())
    {
        qDebug() << sql_query.lastError();
    }
    else
    {
        qDebug() << "table cleared";
    }

    for(int i = 0;i < all_users.size();i++)
    {
        sql_query.prepare(insert_sql);
        sql_query.addBindValue(all_users[i].id);
        sql_query.addBindValue(all_users[i].username);
        sql_query.addBindValue(all_users[i].password);
        sql_query.addBindValue(all_users[i].level);
        sql_query.addBindValue(all_users[i].responsible_plate);
        if(!sql_query.exec())
        {
            qDebug() << sql_query.lastError();
        }
    }
    all_users.clear();
    mainview->close();
}

void Administrators::appoint_or_revoke_moderator()
{
    mod = new Moderatorwindow(mainview->state);
    QString temp;
    if(mod->state == 1)
        temp = "game";
    else if(mod->state == 2)
        temp = "movie";
    else if(mod->state == 3)
        temp = "comic";
    else if(mod->state == 4)
        temp = "music";
    else if(mod->state == 5)
        temp = "sports";
    mod->ui->state->setText("当前板块:" + temp);
    mod->setWindowTitle(QObject::tr(""));
    mod->setWindowModality(Qt::ApplicationModal);
    mod->show();
}

