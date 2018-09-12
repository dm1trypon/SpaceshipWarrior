#include "spaceship.h"
#include "widget.h"
#include "bullet.h"
#include "linksignal.h"
#include "asteroid.h"
#include "enemyspaceship.h"

Bullet::Bullet(QPointF initPos, QGraphicsItem *parent) : QGraphicsLineItem (parent)
{
    setPen(QPen(QBrush(Qt::red), 3));
    setLine(0, 0, 0, -bulletLenght);
    setPos(initPos);
}

void Bullet::advance(int phase)
{
    if (!phase) {
        foreach(QGraphicsItem* item, collidingItems()) {
            Asteroid* obj = qgraphicsitem_cast<Asteroid*>(item);
            EnemySpaceship* objEnemySpaceship = qgraphicsitem_cast<EnemySpaceship*>(item);
            if ((obj) || (objEnemySpaceship)) {
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
