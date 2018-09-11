#include "spaceship.h"
#include "widget.h"
#include "bullet.h"
#include "linksignal.h"
#include "asteroid.h"
#include <QDebug>
#include "enemyspaceship.h"

LinkSignal &EnemySpaceship::getController()
{
    return this->Controller;
}

LinkSignal &Asteroid::getController()
{
    return this->Controller;
}

LinkSignal &Spaceship::getController()
{
    return this->Controller;
}

void LinkSignal::destroy(int var)
{
    if (var == 1) {
        emit signalDestroy();
    }
    if (var == 2){
        qDebug() << "INT VAR:" << var;
        emit signalEndGameMessage();
    }
}
