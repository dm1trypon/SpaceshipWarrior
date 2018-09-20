#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "asteroid.h"
#include "enemyspaceship.h"

#include <QGraphicsPixmapItem>

class Spaceship : public QGraphicsPixmapItem
{
private:
    int xspeed = 0;
    int spaceshipSpeed = 7;
    bool onWidthScreen(int var);
    bool objectDefinition(Asteroid* objAsteroid, EnemySpaceship* objEnemySpaceship);
    bool collision();
    void collisionObjects();
    void endGameMessageSpaceship(int var);
    void stabilizeMoveSpaceship();
    void moveSpaceship();
    void destroyDefinition(QGraphicsItem* item, Asteroid* objAsteroid, EnemySpaceship* objEnemySpaceship);
    qreal SpaceshipPosX();
    qreal SpaceshipPosY();
public:
    Spaceship();
    void advance(int phase);
protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
};

#endif // SPACESHIP_H
