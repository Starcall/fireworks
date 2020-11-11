#ifndef EXPLOSIONFACTORY_H
#define EXPLOSIONFACTORY_H

#include "Explosion.h"

class ExplosionFactory
{
public:
    ExplosionFactory(){};
    Explosion* makeExplosion(QGraphicsItem* parent);
    Explosion* makeExplosion(qint32 x, qint32 y, QGraphicsItem* parent);
};

#endif // EXPLOSIONFACTORY_H
