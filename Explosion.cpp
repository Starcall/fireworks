#include "Explosion.h"
#include "QDebug"
#include "QBrush"

Explosion::Explosion(QGraphicsItem *parent)
{
    setParentItem(parent);
    srand(time(0));
}

Explosion::Explosion(qint32 x, qint32 y, QGraphicsItem *parent) : Explosion(parent)
{
    setRect(0, 0, MIN_EXPLOSION_SIZE, MIN_EXPLOSION_SIZE);
    setPos(x, y);
}

void Explosion::explodeNext()
{
    curState += 1;
    setRect(-explosionsSizes[curState % explosionsSizes.size()] / 2, -explosionsSizes[curState % explosionsSizes.size()] / 2, explosionsSizes[curState % explosionsSizes.size()], explosionsSizes[curState % explosionsSizes.size()]);
    setBrush(QBrush(QColor(rand() % 255, rand() % 255, rand() % 255)));
}
