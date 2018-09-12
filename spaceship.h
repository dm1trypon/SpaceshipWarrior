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
#include "asteroid.h"
#include "enemyspaceship.h"

class Spaceship : public QGraphicsPixmapItem {
private:
    const uint SCREEN_WIDTH_END = 700;
    const int SCREEN_WIDTH_BEGIN = -20;
    const int SCREEN_HEIGHT = 600;
    const int LEFT = 0;
    const int RIGHT = 1;
    const int SEGMENT = 2;
    int xspeed = 0;
    int spaceshipSpeed = 6;
    bool onWidthScreen(int var);
    bool objectDefinition(Asteroid* objAsteroid, EnemySpaceship* objEnemySpaceship);
    bool collision();
    void collisionObjects();
    void endGameMessageSpaceship(int var);
    void stabilizeMoveSpaceship();
    void moveSpaceship();
public:
    //LinkSignal &getController();
    Spaceship(qreal sceneHeight);
    void advance(int phase);
protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
};

#endif // SPACESHIP_H
