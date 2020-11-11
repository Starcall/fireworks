#include "SaluteFactory.h"


Firework* SaluteFactory::makeSalute(qint32 x, qint32 y)
{
    numberOfSalutes += 1;
    auto salute = new Firework(x, y);
    salute->setStep(rand() % 8 - 4, -(rand() % 10));
    emit salutePrepared();
    return salute;
}

Firework *SaluteFactory::makeSalute(qint32 x, qint32 y, double speed)
{
    auto salute = makeSalute(x, y);
    salute->setSpeed(speed);
    return salute;
}

Firework *SaluteFactory::makeSalute(qint32 x, qint32 y, double speed, qint32 lifetime)
{
    auto salute = makeSalute(x, y, speed);
    salute->setLifetime(lifetime);
    return salute;
}
