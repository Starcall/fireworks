#ifndef SALUTE_H
#define SALUTE_H


#include <QGraphicsRectItem>
#include "StaticData.h"
#include "Explosion.h"

class Firework : public QGraphicsRectItem
{
public:
    Firework(qint32 x, qint32 y, QGraphicsItem* parent = 0);


    void makeStep();
    bool canMove();

    bool isNeedDeletions() {
        return needDeletion;
    }

    void setStep(qint32 stepX, qint32 stepY);
    void setSpeed(double speed);
    void setLifetime(qint32 lifetime);

private:
    qint32 movesBeforeExplode = 10;
    qint32 movesBeforeDelete = 30;
    QWidget* parent = 0;
    bool needDeletion = false;

    qint32 stepX = 0;
    qint32 stepY = -1;

    double speedAmplifier = 1;

    void explode();

};

#endif // SALUTE_H
