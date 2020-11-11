#include "ButtonsFactory.h"

QPushButton *ButtonsFactory::makeButton(qint32 x, qint32 y, qint32 width, qint32 height, QString text, QWidget *parent)
{
    QPushButton* createdButton = new QPushButton(text, parent);
    createdButton->setGeometry(x, y, width, height);
    return createdButton;
}
