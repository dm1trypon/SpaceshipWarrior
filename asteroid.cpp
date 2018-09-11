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

Asteroid::Asteroid(qreal xspread) : QGraphicsPixmapItem (nullptr)
{
    setPixmap(QPixmap(":/images/asteroid.png"));
    qreal post = rand() % static_cast<int>(xspread - pixmap().width());
    setPos(post, -100);
}

void Asteroid::advance(int phase)
{
    if (phase) {
        moveBy(0, yspeed);

        if ((data(0).toBool()) || (Asteroid::y() > 800)) {
             if (Asteroid::y() < 800) {
                destroyAsteroidBullet(1);
            }
            else{
                endGameMessageAsteroid(2);
                destroyAsteroidRange();
            }
        }
    }
}

void Asteroid::destroyAsteroidBullet(int var)
{
    Controller.destroy(var);
    delete this;
}

void Asteroid::destroyAsteroidRange()
{
    delete this;
}

int Asteroid::type() const
{
    return Type;
}

void Asteroid::endGameMessageAsteroid(int var)
{
    Controller.destroy(var);
}
