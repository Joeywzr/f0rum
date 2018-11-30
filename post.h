#ifndef POST_H
#define POST_H
#include <QString>
#include <QVector>
#include <comment.h>

typedef enum
{
    game=0,
    movie,
    comic,
    music,
    sports
}Category;


class Post
{
public:
    Post();
    QString id = 0;
    QString poster_name;
    QString title;
    QString content;
    QString time;
    QVector<Comment> comment;
};

#endif // POST_H
