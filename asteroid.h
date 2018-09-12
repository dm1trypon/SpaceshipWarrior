#ifndef ASTEROID_H
#define ASTEROID_H

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

class Asteroid : public QGraphicsPixmapItem {
public:
    const uint SCREEN_HEIGHT = 800;
    enum { Type = UserType + 1};
    Asteroid(qreal xspread);
    void advance(int phase);
    //LinkSignal &getController();
    int type() const;
private:
    int yspeed = 2;
    bool collision();
    bool onScreen();
    void endGame();
    void endGameMessageAsteroid(int var);
    void destroyAsteroidBullet(int var);
    //void destroyAsteroidRange();
};
#endif // ASTEROID_H
