#include "spaceship.h"
#include "widget.h"
#include "bullet.h"
#include "linksignal.h"
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
#include <QDebug>

Asteroid::Asteroid(qreal xspread) : QGraphicsPixmapItem (nullptr)
{
    setPixmap(QPixmap(":/images/asteroid.png"));
    qreal post = rand() % static_cast<int>(xspread - pixmap().width());
    setPos(post, -100);
}

void Asteroid::advance(int phase)
{
    if (phase <= 0) {
        return;
    }

    moveBy(0, yspeed);

    if (!onScreen()) {
        endGame();
    }

    if (collision()) {
        destroyAsteroidBullet(DESTROY);
    }
}

bool Asteroid::collision()
{
    return data(0).toBool();
}

bool Asteroid::onScreen()
{
    return Asteroid::y() < SCREEN_HEIGHT ? true : false;
}

void Asteroid::endGame()
{
    endGameMessageAsteroid(ENDGAME);
    qDebug() << ENDGAME;
    delete this;
}

void Asteroid::destroyAsteroidBullet(int var)
{
    LinkSignal::Instance().destroy(var);
    delete this;
}

int Asteroid::type() const
{
    return Type;
}

void Asteroid::endGameMessageAsteroid(int var)
{
    LinkSignal::Instance().destroy(var);
}
