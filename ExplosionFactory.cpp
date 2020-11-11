#include "ExplosionFactory.h"


Explosion *ExplosionFactory::makeExplosion(QGraphicsItem *parent = 0)
{
    return new Explosion(parent);
}

Explosion *ExplosionFactory::makeExplosion(qint32 x, qint32 y, QGraphicsItem *parent = 0)
{
    return new Explosion(x, y, parent);
}
