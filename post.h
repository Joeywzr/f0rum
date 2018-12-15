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
    //重载Post类<<运算符
    friend QTextStream& operator << (QTextStream &fout, Post posts);
    //重载Post类>>运算符
    friend QTextStream& operator >> (QTextStream &fin, Post &posts);
};

#endif // POST_H
