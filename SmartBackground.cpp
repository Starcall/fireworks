#include "SmartBackground.h"
#include "QDebug"
#include <iostream>

void SmartBackground::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
   // emit spawnSalute(event->x(), event->y());

    qDebug() <<  "Mouse Press event";
}
