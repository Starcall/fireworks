#ifndef BUTTONSFACTORY_H
#define BUTTONSFACTORY_H
#include <QPushButton>
#include <QWidget>

class ButtonsFactory
{
public:
    ButtonsFactory() {};
    QPushButton* makeButton(qint32 x, qint32 y, qint32 width, qint32 height, QString text, QWidget* parent = 0);
};

#endif // BUTTONSFACTORY_H
