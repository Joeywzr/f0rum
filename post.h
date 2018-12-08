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


    friend QTextStream& operator << (QTextStream &fout, QHash<Category,QVector<Post>> &all_post)
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
                    fout << " $$$ ";
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
        QList<QString> list;
        QList<QString>::iterator i;
        list = str.split(" $$$ ");
        if(list.size() <= 1)
            return fin;

        for(i = list.begin();i != list.end();)
        {
            posts.state = *i;i++;
            posts.id = (*i).toInt();i++;
            posts.poster_name = *i;i++;
            posts.time = *i;i++;
            posts.comment_num = (*i).toInt();i++;
            posts.title = *i;i++;
            posts.content = *i;i++;
            for(int j = 0;j < posts.comment_num;j++)
            {
                com.username = *i;i++;
                com.time = *i;i++;
                com.content = *i;i++;
                posts.comment.push_back(com);
            }
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
            posts.comment.clear();
        }
        return fin;
    }
};

#endif // POST_H
