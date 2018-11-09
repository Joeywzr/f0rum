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

typedef struct info_post
{
    QString id;
    QString title;
    QString content;
    QString time;
    Comment comment;

}INFO_POST;

class Post
{
public:
    Post();
    QVector<INFO_POST> info;

};

#endif // POST_H
