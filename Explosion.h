#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <QGraphicsEllipseItem>
#include "StaticData.h"

class Explosion : public QGraphicsEllipseItem
{
public:
    Explosion(QGraphicsItem* parent = 0);
    Explosion(qint32 x, qint32 y, QGraphicsItem* parent = 0);
    void explodeNext();
private:
    const quint32 MIN_EXPLOSION_SIZE = 50;
    const quint32 MEAN_EXPLOSION_SIZE = 100;
    const quint32 MAX_EXPLOSION_SIZE = 150;

    std::vector<qint32> explosionsSizes = {50, 100, 150};
    std::vector<QColor> explosionsColors = {Qt::green, Qt::blue, Qt::yellow};
    qint32 curState = -1;



};

#endif // EXPLOSION_H
