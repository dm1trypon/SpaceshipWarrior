#ifndef BULLET_H
#define BULLET_H

#include "asteroid.h"
#include "enemyspaceship.h"

class Bullet : public QGraphicsLineItem
{
public:
    Bullet(QPointF initPos, QGraphicsItem* parent);
    void advance(int phase);
private:
    int lifeEnemySpaceship = 2;
    int yspeed = 4;
    int bulletLenght = 10;
    bool onScreen();
    bool collision();
    bool objectDefinition(Asteroid* objAsteroid, EnemySpaceship* objEnemySpaceship);
    void moveBullet();
    void collisionObjects();
    void destroyDefinition(QGraphicsItem* item, Asteroid* objAsteroid, EnemySpaceship* objEnemySpaceship);
};

#endif // BULLET_H
