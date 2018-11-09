#ifndef COMMENT_H
#define COMMENT_H
#include <QString>
#include <QVector>

typedef struct info_com
{
    QString content;
    QString time;
}INFO_COM;


class Comment
{
public:
    Comment();
    QVector<INFO_COM> info;
};

#endif // COMMENT_H
