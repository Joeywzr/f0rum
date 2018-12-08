#ifndef ANONYMOUS_H
#define ANONYMOUS_H
#include "ordinary_user.h"

class Anonymous:public Ordinary_user
{
    Q_OBJECT
public:
    Anonymous();
    void init_class();
public slots:
    void user_information();
};

#endif // ANONYMOUS_H
