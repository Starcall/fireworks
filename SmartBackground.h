#ifndef SMARTBACKGROUND_H
#define SMARTBACKGROUND_H

#endif // SMARTBACKGROUND_H

#include <QMouseEvent>
#include <QGraphicsRectItem>

class SmartBackground : public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    SmartBackground(){};
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
signals:
    void spawnSalute(qint32 x, qint32 y);

};
