#ifndef ENEMYSPACESHIP_H
#define ENEMYSPACESHIP_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsPixmapItem>
#include <QTimer>
//#include "linksignal.h"

class EnemySpaceship : public QGraphicsPixmapItem
{
public:
    enum { Type = UserType + 1};
    EnemySpaceship(qreal xspread);
    void advance(int phase);
    int type() const;
private:
    const uint SCREEN_HEIGHT = 800;
    const int SCREEN_TOP = -100;
    int yspeed = 3;
    int xspeed = 0;
    int life = 3;
    bool change = false;
    bool onScreen();
    bool collision();
    void endGame();
    int changeXspeed(int xspeed);
    void destroyEnemySpaceshipBullet(int var);
public slots:
    void lifeChangerEnemySpaceship();
};


#endif // ENEMYSPACESHIP_H
