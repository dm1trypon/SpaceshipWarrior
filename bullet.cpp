#include "spaceship.h"
#include "widget.h"
#include "bullet.h"
#include "linksignal.h"
#include "asteroid.h"

#define CIRCLE_SIZE 50
#define SPACESHIP_SPEED 6
#define BULLET_LENGHT 10
#define BULLET_SPEED 4

Bullet::Bullet(QPointF initPos, QGraphicsItem *parent) : QGraphicsLineItem (parent)
{
    yspeed = BULLET_SPEED;
    setPen(QPen(QBrush(Qt::red), 3));
    setLine(0, 0, 0, -BULLET_LENGHT);
    setPos(initPos);
}

void Bullet::advance(int phase)
{
    if (!phase) {
        foreach(QGraphicsItem* item, collidingItems()) {
            Asteroid* obj = qgraphicsitem_cast<Asteroid*>(item);
            if (obj) {
                item->setData(0, true);
                setData(0, true);
            }
        }
    }
    else {
        moveBy(0, -yspeed);
        if (data(0).toBool() || (Bullet::y() < -100)) {
            delete this;
        }
    }
}
