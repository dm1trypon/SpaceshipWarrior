#ifndef BULLET_H
#define BULLET_H

#include "asteroid.h"
#include "enemyspaceship.h"

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsPixmapItem>
#include <QTimer>

class Bullet : public QGraphicsLineItem
{
public:
    Bullet(QPointF initPos, QGraphicsItem* parent);
    void advance(int phase);
private:
    const int SCREEN_TOP = -100;
    int lifeEnemySpaceship = 2;
    int yspeed = 4;
    int bulletLenght = 10;
    bool onScreen();
    bool collision();
    bool objectDefinition(Asteroid* objAsteroid, EnemySpaceship* objEnemySpaceship);
    void checkDestroyEnemySpaceship(QGraphicsItem* item);
    void moveBullet();
    void collisionObjects();
    void destroyDefinition(QGraphicsItem* item, Asteroid* objAsteroid, EnemySpaceship* objEnemySpaceship);

};

#endif // BULLET_H
