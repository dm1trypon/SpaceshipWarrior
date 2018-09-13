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

EnemySpaceship::EnemySpaceship(qreal xspread) : QGraphicsPixmapItem (nullptr)
{
    setPixmap(QPixmap(":/images/spaceship-big.png"));
    qreal post = rand() % static_cast<int>(xspread - pixmap().width());
    setPos(post, SCREEN_TOP);
}

void EnemySpaceship::advance(int phase)
{
    if (phase <= 0) {
        return;
    }
    moveBy(xspeed, yspeed);

    if (!onScreen()) {
        endGame();
    }

    if (collision()) {
        destroyEnemySpaceshipBullet(DESTROY);
    }
}

void EnemySpaceship::lifeChangerEnemySpaceship()
{
    life--;
    if(!life)
    {
        delete this;
    }
}

bool EnemySpaceship::collision()
{
    return data(0).toBool();
}

bool EnemySpaceship::onScreen()
{
    return this->y() < SCREEN_HEIGHT;
}

void EnemySpaceship::endGame()
{
    LinkSignal::Instance().destroy(ENDGAME);
    delete this;
}

void EnemySpaceship::destroyEnemySpaceshipBullet(int var)
{
    LinkSignal::Instance().destroy(var);
}

int EnemySpaceship::type() const
{
    return Type;
}
