#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "Firework.h"
#include <QGraphicsView>
#include <deque>
#include <QPushButton>
#include "StaticData.h"
#include "SaluteFactory.h"
#include "ExplosionFactory.h"
#include "Explosion.h"
#include <QSlider>
#include "ButtonsFactory.h"
#include <QLabel>

class Game : public QGraphicsView
{
    Q_OBJECT
public:
    Game(QWidget* parent=0);

    void mousePressEvent(QMouseEvent *event);

    QGraphicsScene* scene;


signals:
    void alarmSalute(qint32 x, qint32 y);

public slots:
    void addSalute(Firework* salute);
    void addExplosion(Explosion* explosion);
    void makeNewRandomSaluteObject();
    void makeNewSaluteObject(qint32 x, qint32 y);
    void flipMenu();
    void updateCounter();

private:
    std::vector<Firework*> salutes;
    std::vector<Explosion*> explosions;
    void moveAndReDraw();
    QPushButton* exitButton = 0;
    QPushButton* cancelExitButton = 0;
    QPushButton* mainMenuButton = 0;

    QGraphicsRectItem* speedSliderRect = 0;
    QSlider* speedSlider = 0;

    QGraphicsRectItem* lifetimeSliderRect = 0;
    QSlider* lifetimeSlider = 0;

    QLabel* numberOfSalutes = 0;

    SaluteFactory* saluteFactory = 0;
    std::unique_ptr<ExplosionFactory> explosionFactory = 0;
    std::unique_ptr<ButtonsFactory> buttonsFactory = 0;


};
#endif // MAINWINDOW_H
