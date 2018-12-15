#include "Post.h"

Post::Post()
{


}
//重载Post类<<运算符
friend QTextStream& Post::operator << (QTextStream &fout, Post posts)
{
    bool is_first = true;//是否是每个帖子的的开头
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
            posts = p[j];
            if(!is_first)
                fout << " ### ";   //把每个帖子用" ### "分隔
            fout << s << " $$$ ";  //把每个帖子的内部信息用" $$$ "分隔
            fout << QString::number(posts.id) << " $$$ ";
            fout << posts.poster_name << " $$$ ";
            fout << posts.time << " $$$ ";
            fout << QString::number(posts.comment_num) << " $$$ ";
            fout << posts.title << " $$$ ";
            fout << posts.content;
            if(posts.comment.size() != 0)
                fout << " $$$ ";
            for(int k = 0;k < posts.comment.size();k++)
            {
                fout << posts.comment[k].username << " $$$ ";
                fout << posts.comment[k].time << " $$$ ";
                fout << posts.comment[k].content;
                if(k != posts.comment.size() - 1)
                    fout << " $$$ ";
            }
            is_first = false;
        }
    }
    return fout;
}
//重载Post类>>运算符
friend QTextStream& operator >> (QTextStream &fin, Post &posts)
{
    QString str;
    str = fin.readAll();
    QList<QString> list1, list2;
    QList<QString>::iterator i;
    bool flag = true;
    list1 = str.split(" ### ");//按" ### "分隔读取各个帖子

    for(i = list1.begin();i != list1.end();i++)
    {
        list2 = (*i).split(" $$$ ");//按" $$$ "分隔读取帖子内部信息
        if(list2.size() != 7 + list2[4].toInt()*3)//如果帖子内部信息数量不对应
            posts.post_error++;
        else
        {
            posts.state = list2[0];
            if(posts.state != "game" &&posts.state != "movie" &&posts.state != "comic" &&posts.state != "music" && posts.state != "sports")
                flag = false;
            posts.id = list2[1].toInt();
            posts.poster_name = list2[2];
            posts.time = list2[3];
            posts.comment_num = list2[4].toInt();
            posts.title = list2[5];
            posts.content = list2[6];
            //读取评论信息
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
            if(flag)//如果没错误就读入该帖子信息
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
            else//若帖子有错则跳过该帖子不读入
            {
                posts.post_error++;
                flag = true;
            }
            posts.comment.clear();
        }
    }
    return fin;
}
