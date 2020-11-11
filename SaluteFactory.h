#ifndef SALUTEFACTORY_H
#define SALUTEFACTORY_H

#include "Firework.h"
#include "StaticData.h"

class SaluteFactory : public QObject
{
    Q_OBJECT

public:
    SaluteFactory() {
        srand(time(0));
    };
    Firework* makeSalute(qint32 x, qint32 y);
    Firework* makeSalute(qint32 x, qint32 y, double speed);
    Firework* makeSalute(qint32 x, qint32 y, double speed, qint32 lifetime);
    qint32 numberOfSalutes = 0;

signals:
    void salutePrepared();

};

#endif // SALUTEFACTORY_H
