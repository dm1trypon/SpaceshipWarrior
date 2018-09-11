#include "spaceship.h"
#include "widget.h"
#include "bullet.h"
#include "linksignal.h"
#include "asteroid.h"

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <widget.cpp>
#include "enemyspaceship.h"

void Spaceship::endGameMessageSpaceship(int var)
{
    Controller.destroy(var);
}

Spaceship::Spaceship::Spaceship(qreal sceneHeight) : QGraphicsPixmapItem(nullptr)
{
    setPixmap(QPixmap(":/images/spaceship.png"));
    setPos(0, sceneHeight - pixmap().height());
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
}

void Spaceship::advance(int phase)
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
        if ((Spaceship::x() <= 700) && (Spaceship::x() >= -20)) {
            moveBy(xspeed, 0);
        }
        else {
            if ((Spaceship::x() >= 700)) {
                Spaceship::setPos(699, 600 - pixmap().height());
            }
            if ((Spaceship::x() <= -20)) {
                Spaceship::setPos(-19, 600 - pixmap().height());
            }
        }
        if (data(0).toBool()) {
            endGameMessageSpaceship(2);
            delete this;
        }
    }
}

void Spaceship::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Left:
        xspeed = - spaceshipSpeed;
        break;
    case Qt::Key_Right:
        xspeed = spaceshipSpeed;
        break;
    case Qt::Key_Space:
        scene()->addItem(new Bullet(mapToScene(QPointF(pixmap().width()/2, 0)), nullptr));
        break;
    default:
        break;
    }
}

void Spaceship::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Left:
        xspeed = 0;
        break;
    case Qt::Key_Right:
        xspeed = 0;
        break;
    default:
        break;
    }
}
