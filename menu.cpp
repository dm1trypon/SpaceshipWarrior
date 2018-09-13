#include "menu.h"
#include "widget.h"

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QDebug>

Menu::Menu()
{
    //descriptionMenu(30, "Unispace", "New Game", Qt::red, 100, static_cast<int>(sceneHeight));
}

//void Menu::descriptionMenu(int size, QString fontType, QString textData, QColor textColor, int setPosX, int setPosY)
//{
//    QFont fontLose;
//    fontLose.setPointSize(size);
//    fontLose.setFamily(fontType);
//    this->setPos(setPosX, setPosY);
//    this->setDefaultTextColor(textColor);
//    this->setFont(fontLose);
//}

//void Menu::mousePressEvent(QGraphicsSceneMouseEvent *event)
//{
//    delete this;
//}
