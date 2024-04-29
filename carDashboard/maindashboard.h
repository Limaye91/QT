#ifndef MAINDASHBOARD_H
#define MAINDASHBOARD_H
#include <QDebug>
#include "../data/data.h"
class maindashboard
{
public:
    maindashboard();

public slots:
    void lastusermain(data *obj);
};

#endif // MAINDASHBOARD_H
