#ifndef POST_H
#define POST_H
#include "headers.h"
#include "comment.h"


class Post
{
public:
    Post();
    QString id = 0;
    QString poster_name;
    QString title;
    QString content;
    QString time;
    QString state;
    QVector<Comment> comment;
};

#endif // POST_H
