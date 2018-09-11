#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include "linksignal.h"

class Spaceship : public QGraphicsPixmapItem {
private:
    int xspeed = 0;
    int spaceshipSpeed = 6;
    LinkSignal Controller;
    void endGameMessageSpaceship(int var);
public:
    LinkSignal &getController();
    Spaceship(qreal sceneHeight);
    void advance(int phase);
protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
};

#endif // SPACESHIP_H
