#include "Game.h"

#include <QGraphicsRectItem>
#include <SmartBackground.h>
#include "SaluteFactory.h"
#include "ButtonsFactory.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QRect>
#include <QTimer>
#include <QSlider>
#include <QLabel>
#include <QImage>
#include <QResource>

Game::Game(QWidget *parent)
{
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    setBackgroundBrush(QBrush(QImage(":/resources/images/background.svg")));
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    buttonsFactory = std::make_unique<ButtonsFactory>(ButtonsFactory());
    saluteFactory = new SaluteFactory();
    explosionFactory = std::make_unique<ExplosionFactory>(ExplosionFactory());

    mainMenuButton = buttonsFactory->makeButton(10, WINDOW_HEIGHT - 10 - MAIN_MENU_BUTTON_HEIGHT, MAIN_MENU_BUTTON_WIDTH, MAIN_MENU_BUTTON_HEIGHT, "", this);
    mainMenuButton->setStyleSheet({"QPushButton { padding: 0; border: none; image : url(:/resources/images/mmbutton.svg)}"});

    cancelExitButton = buttonsFactory->makeButton(10, WINDOW_HEIGHT - 10 - CANCEL_EXIT_BUTTON_HEIGHT, CANCEL_EXIT_BUTTON_WIDTH, CANCEL_EXIT_BUTTON_HEIGHT, "", this);
    cancelExitButton->setStyleSheet({"QPushButton { padding: 0; border: none; image : url(:/resources/images/cancelbutton.svg)}"});

    exitButton = buttonsFactory->makeButton(10 + CANCEL_EXIT_BUTTON_WIDTH, WINDOW_HEIGHT - 10 - CANCEL_EXIT_BUTTON_HEIGHT, CANCEL_EXIT_BUTTON_WIDTH, CANCEL_EXIT_BUTTON_HEIGHT, "", this);
    exitButton->setStyleSheet({"QPushButton { padding: 0; border: none; image : url(:/resources/images/exitButton.svg)}"});

    speedSliderRect = new QGraphicsRectItem(0, 0, SPEED_SLIDER_RECT_WIDTH, SPEED_SLIDER_RECT_HEIGHT);
    speedSliderRect->setPos(10 + 10 + MAIN_MENU_BUTTON_WIDTH, WINDOW_HEIGHT - 10 - SPEED_SLIDER_RECT_HEIGHT);
    speedSliderRect->setBrush(QBrush(QImage(":/resources/images/speedamplifier.svg")));
    scene->addItem(speedSliderRect);

    speedSlider = new QSlider(Qt::Horizontal, this);
    speedSlider->setGeometry(10 + 10 + 10 + MAIN_MENU_BUTTON_WIDTH, WINDOW_HEIGHT - 10 - SPEED_SLIDER_HEIGHT, SPEED_SLIDER_WIDTH, SPEED_SLIDER_HEIGHT);
    speedSlider->setMaximum(5);
    speedSlider->setMinimum(1);

    lifetimeSliderRect = new QGraphicsRectItem(0, 0, LIFETIME_SLIDER_RECT_WIDTH, LIFETIME_SLIDER_RECT_HEIGHT);
    lifetimeSliderRect->setPos(10 + 10 + 10 + MAIN_MENU_BUTTON_WIDTH + SPEED_SLIDER_RECT_WIDTH, WINDOW_HEIGHT - 10 - LIFETIME_SLIDER_RECT_HEIGHT);
    lifetimeSliderRect->setBrush(QBrush(QImage(":/resources/images/timebeforeexplosion.svg")));
    scene->addItem(lifetimeSliderRect);

    lifetimeSlider = new QSlider(Qt::Horizontal, this);
    lifetimeSlider->setGeometry(10 + 10 + 10 + 10 + MAIN_MENU_BUTTON_WIDTH + SPEED_SLIDER_RECT_WIDTH, WINDOW_HEIGHT - 10 - LIFETIME_SLIDER_HEIGHT , LIFETIME_SLIDER_WIDTH, LIFETIME_SLIDER_HEIGHT);
    lifetimeSlider->setMaximum(35);
    lifetimeSlider->setMinimum(10);

    numberOfSalutes = new QLabel(this);
    numberOfSalutes->setGeometry(10 + 10 + 10 + 10 + 10 + MAIN_MENU_BUTTON_WIDTH + SPEED_SLIDER_RECT_WIDTH + LIFETIME_SLIDER_RECT_WIDTH, WINDOW_HEIGHT - 10 - NUMBER_OF_SALUTES_LABEL_HEIGHT, NUMBER_OF_SALUTES_LABEL_WIDTH, NUMBER_OF_SALUTES_LABEL_HEIGHT);
    numberOfSalutes->setText("Number of salutes: " + QString::number(saluteFactory->numberOfSalutes));
    numberOfSalutes->setStyleSheet({"QLabel { color : white }"});

    cancelExitButton->setHidden(true);
    exitButton->setHidden(true);



    connect(mainMenuButton, &QPushButton::released, this, &Game::flipMenu);

    connect(cancelExitButton, &QPushButton::released, this, &Game::flipMenu);

    connect(exitButton, &QPushButton::released, this,  &QWidget::close);

    connect(saluteFactory, &SaluteFactory::salutePrepared, this, &Game::updateCounter);

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Game::moveAndReDraw);
    timer->start(50);

    QTimer* spawnSaluteTimer = new QTimer(this);
    connect(spawnSaluteTimer, &QTimer::timeout, this, &Game::makeNewRandomSaluteObject);
    spawnSaluteTimer->start(1000);
}

void Game::mousePressEvent(QMouseEvent *event)
{
    makeNewSaluteObject(event->x(), event->y());
    QGraphicsView::mousePressEvent(event);
}

void Game::makeNewSaluteObject(qint32 x, qint32 y) {
    auto newSalute = saluteFactory->makeSalute(x, y, speedSlider->value(), lifetimeSlider->value());
    auto newExplosion = explosionFactory->makeExplosion(newSalute);
    addSalute(newSalute);
    addExplosion(newExplosion);
}

void Game::addSalute(Firework *salute)
{
    scene->addItem(salute);
    salutes.push_back(salute);
}

void Game::addExplosion(Explosion *explosion)
{
    explosions.push_back(explosion);
}

void Game::makeNewRandomSaluteObject()
{
    qint32 x = rand() % WINDOW_WIDTH;
    qint32 y = rand() % WINDOW_HEIGHT;
    makeNewSaluteObject(x, y);
}
void Game::flipMenu()

{
    cancelExitButton->setHidden((cancelExitButton->isHidden() + 1) % 2);
    exitButton->setHidden((exitButton->isHidden() + 1) % 2);
    mainMenuButton->setHidden((mainMenuButton->isHidden() +1) % 2);
}

void Game::updateCounter()
{
    numberOfSalutes->setText("Number of salutes: " + QString::number(saluteFactory->numberOfSalutes));
}


void Game::moveAndReDraw()
{
    std::vector<Firework*> actualSalutes;
    for (auto salute : salutes) {
        if (salute->isNeedDeletions() == false)
            actualSalutes.push_back(salute);
        else {
            scene->removeItem(salute);
            delete salute;
        }
    }
    salutes = actualSalutes;
    for (auto salute : salutes) {
        salute->makeStep();
    }
}
