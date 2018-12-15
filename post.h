#ifndef POST_H
#define POST_H
#include "headers.h"
#include "comment.h"
class Post;
extern QHash<Category,QVector<Post>> all_post;//所有帖子
extern Comment com;
class Post
{
public:
    Post();
    QString state;//帖子板块
    int id = 0;//帖子id
    QString poster_name;//发送者用户名
    QString title;//帖子标题
    QString content;//帖子内容
    QString time;//帖子时间
    int comment_num = 0;//评论数量
    QVector<Comment> comment;//帖子评论
    int post_error = 0;


    friend QTextStream& operator << (QTextStream &fout, Post posts)
    {
        bool is_first = true;
        for(int i = 1;i <= 5;i++)
        {
            Category state;
            QString s;
            switch (i) {
            case 1:
                state = game;s = "game";break;
            case 2:
                state = movie;s = "movie";break;
            case 3:
                state = comic;s = "comic";break;
            case 4:
                state = music;s = "music";break;
            case 5:
                state = sports;s = "sports";break;
            default:break;
            }
            QVector<Post> p = all_post[state];
            for(int j = 0;j < p.size();j++)
            {
                if(!is_first)
                    fout << " ### ";
                fout << s << " $$$ ";
                fout << QString::number(p[j].id) << " $$$ ";
                fout << p[j].poster_name << " $$$ ";
                fout << p[j].time << " $$$ ";
                fout << QString::number(p[j].comment_num) << " $$$ ";
                fout << p[j].title << " $$$ ";
                fout << p[j].content;
                if(p[j].comment.size() != 0)
                    fout << " $$$ ";
                for(int k = 0;k < p[j].comment.size();k++)
                {
                    fout << p[j].comment[k].username << " $$$ ";
                    fout << p[j].comment[k].time << " $$$ ";
                    fout << p[j].comment[k].content;
                    if(k != p[j].comment.size() - 1)
                        fout << " $$$ ";
                }
                is_first = false;
            }
        }
        return fout;
    }

    friend QTextStream& operator >> (QTextStream &fin, Post &posts)
    {
        QString str;
        str = fin.readAll();
        QList<QString> list1, list2;
        QList<QString>::iterator i;
        bool flag = true;
        list1 = str.split(" ### ");

        for(i = list1.begin();i != list1.end();i++)
        {
            list2 = (*i).split(" $$$ ");
            if(list2.size() != 7 + list2[4].toInt()*3)
            {
                posts.post_error++;
                qDebug() << "cuola" << endl;
            }
            else
            {
                posts.state = list2[0];
                if(posts.state != "game" &&
                        posts.state != "movie" &&
                        posts.state != "comic" &&
                        posts.state != "music" &&
                        posts.state != "sports")
                    flag = false;
                posts.id = list2[1].toInt();
                posts.poster_name = list2[2];
                posts.time = list2[3];
                posts.comment_num = list2[4].toInt();
                posts.title = list2[5];
                posts.content = list2[6];
                for(int j = 7;j < list2.size();j++)
                {
                    if(j % 3 == 1)
                        com.username = list2[j];
                    else if(j % 3 == 2)
                        com.time = list2[j];
                    else if(j % 3 == 0)
                    {
                        com.content = list2[j];
                        posts.comment.push_back(com);
                    }
                }
                if(flag)
                {
                    if(posts.state == "game")
                        all_post[game].push_back(posts);
                    else if(posts.state == "movie")
                        all_post[movie].push_back(posts);
                    else if(posts.state == "comic")
                        all_post[comic].push_back(posts);
                    else if(posts.state == "music")
                        all_post[music].push_back(posts);
                    else if(posts.state == "sports")
                        all_post[sports].push_back(posts);
                }
                else
                {
                    posts.post_error++;
                    flag = true;
                }
                posts.comment.clear();
            }

        }
        return fin;
    }
};

#endif // POST_H
