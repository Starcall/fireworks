#include "Firework.h"
#include <QDebug>
#include <QBrush>

Firework::Firework(qint32 x, qint32 y, QGraphicsItem *parent)
{
    setRect(0, 0, PARTICLE_SIZE, PARTICLE_SIZE);
    setPos(x, y);
    setParentItem(parent);
    setBrush(QBrush(QColor(rand() % 255, rand() % 255, rand() % 255)));
    qDebug() << "Constructor" << " " << pos().x() << " " << pos().y();

}

void Firework::makeStep()
{
    movesBeforeExplode -= 1;
    if (movesBeforeExplode <= 0) {
        movesBeforeDelete -=1;
        if (movesBeforeDelete == 0) {
            needDeletion = true;
        }
        explode();
        return;
    }
    if (canMove()) {
        setPos(pos().x() + stepX * speedAmplifier, pos().y() + stepY * speedAmplifier);
    } else {
        needDeletion = true;
    }
}

bool Firework::canMove()
{
    qint32 newX = pos().x() + stepX * speedAmplifier;
    qint32 newY = pos().y() + stepY * speedAmplifier;
    if (newX < 0 || newX >WINDOW_WIDTH  || newY < 0 || newY >WINDOW_HEIGHT )
        return false;
    return true;
}

void Firework::setStep(qint32 stepX, qint32 stepY)
{
    this->stepX = stepX;
    this->stepY = stepY;
}

void Firework::setSpeed(double speed)
{
    speedAmplifier = speed;
}

void Firework::setLifetime(qint32 lifetime)
{
    movesBeforeExplode = lifetime;
}

void Firework::explode()
{
    qDebug() << "Exploded " << childItems().size();
    for (auto explosion : childItems()) {
        qDebug() << "Have Item";
        dynamic_cast<Explosion*>(explosion)->explodeNext();
    }
    //newParticle = saluteFactory-->
}


