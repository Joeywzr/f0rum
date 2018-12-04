#ifndef POST_H
#define POST_H
#include "headers.h"
#include "comment.h"

class Post
{
public:
    Post();
    QString id;//帖子id
    QString poster_name;//发送者用户名
    QString title;//帖子标题
    QString content;//帖子内容
    QString time;//帖子时间
    QString state;//帖子板块
    QVector<Comment> comment;//帖子评论
};

#endif // POST_H
