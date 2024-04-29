#include "maindashboard.h"

maindashboard::maindashboard() {}

void maindashboard::lastusermain(data *obj)
{
    qDebug() << obj->getUsername();
}
