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

#include "enemyspaceship.h"

EnemySpaceship::EnemySpaceship(qreal xspread) : QGraphicsPixmapItem (nullptr)
{
    setPixmap(QPixmap(":/images/spaceship-big.png"));
    qreal post = rand() % static_cast<int>(xspread - pixmap().width());
    setPos(post, -100);
}

void EnemySpaceship::advance(int phase)
{
    if (phase) {
        moveBy(0, yspeed);

        if ((data(0).toBool()) || (EnemySpaceship::y() > 800)) {
             if (EnemySpaceship::y() < 800) {
                destroyEnemySpaceshipBullet(1);
            }
            else{
                endGameMessageEnemySpaceship(2);
                destroyEnemySpaceshipRange();
            }
        }
    }
}

void EnemySpaceship::destroyEnemySpaceshipBullet(int var)
{
    Controller.destroy(var);
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
    Controller.destroy(var);
}
