#include "enemyspaceship.h"
#include "const.h"
#include "linksignal.h"

#include <QWidget>
#include <QDebug>
#include <QTimer>

EnemySpaceship::EnemySpaceship(qreal xspread) : QObject(), QGraphicsPixmapItem (nullptr)
{
    setPixmap(QPixmap(":/images/spaceship-big.png"));
    srand(static_cast<uint>(time(nullptr)));
    setPos(getRandomWidth(xspread), SCREEN_TOP);
    connect(&LinkSignal::Instance(), SIGNAL(signalSpeedEnemySpaceshipSet(int)), this, SLOT(speedEnemySpaceshipSet(int)));
    moveEnemySpaceShipXTimer = new QTimer(this);
    connect(moveEnemySpaceShipXTimer, SIGNAL( timeout()), this, SLOT(setMoveX()));
    moveEnemySpaceShipXTimer->start(1000);
}

qreal EnemySpaceship::getRandomWidth(qreal xspread)
{
    return rand() % static_cast<int>(xspread - pixmap().width());
}

void EnemySpaceship::setMoveX()
{
    switch (xspeed)
    {
    case 2:
        xspeed -= 4;
        break;
    case -2:
        xspeed += 4;
        break;
    }
}

void EnemySpaceship::speedEnemySpaceshipSet(int speedEnemySpaceship)
{
    yspeed = speedEnemySpaceship;;
}

void EnemySpaceship::advance(int phase)
{
    if (phase <= 0) {
        return;
    }
    moveBy(xspeed, yspeed);
    if (!onScreen()) {
        destroy(ENDGAME);
    }

    if (collision()) {
        destroy(DESTROY_ENEMY_SPACESHIP);
    }
}

bool EnemySpaceship::collision()
{
    return data(0).toBool();
}

bool EnemySpaceship::onScreen()
{
    return this->y() < SCREEN_HEIGHT + 200;
}

void EnemySpaceship::destroy(int var)
{
    switch (var)
    {
    case ENDGAME:
        LinkSignal::Instance().destroy(var);
        delete this;
        break;
    case DESTROY_ENEMY_SPACESHIP:
        LinkSignal::Instance().destroy(var);
        break;
    };
}

int EnemySpaceship::type() const
{
    return Type;
}
