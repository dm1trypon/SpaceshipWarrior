#include "spaceship.h"
#include "widget.h"
#include "bullet.h"
#include "linksignal.h"
#include "asteroid.h"
#include "enemyspaceship.h"

#include <QDebug>

void LinkSignal::destroy(int var)
{
    switch (var) {
    case DESTROY:
        emit signalDestroy();
        break;
    case ENDGAME:
        emit signalEndGameMessage();
        break;
    default:
        break;
    }
}

LinkSignal &LinkSignal::Instance()
{
    static LinkSignal theSingleInstance;
    return theSingleInstance;
}
