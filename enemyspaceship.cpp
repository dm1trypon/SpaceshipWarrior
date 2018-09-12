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
    setPos(post, -100);
}

void EnemySpaceship::advance(int phase)
{
    if (phase <= 0) {
        return;
    }

    moveBy(0, yspeed);

    if (!onScreen()) {
        endGame();
    }

    if (collision()) {
        destroyEnemySpaceshipBullet(DESTROY);
    }
}

bool EnemySpaceship::collision()
{
    return data(0).toBool();
}

bool EnemySpaceship::onScreen()
{
    return EnemySpaceship::y() < SCREEN_HEIGHT ? true : false;
}

void EnemySpaceship::endGame()
{
    endGameMessageEnemySpaceship(ENDGAME);
    qDebug() << ENDGAME;
    delete this;
}

void EnemySpaceship::destroyEnemySpaceshipBullet(int var)
{
    LinkSignal::Instance().destroy(var);
    delete this;
}

void EnemySpaceship::destroyEnemySpaceshipRange()
{
    delete this;
}

int EnemySpaceship::type() const
{
    return Type;
}

void EnemySpaceship::endGameMessageEnemySpaceship(int var)
{
    LinkSignal::Instance().destroy(var);
}
