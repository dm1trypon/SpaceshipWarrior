#include "spaceship.h"
#include "widget.h"
#include "bullet.h"
#include "linksignal.h"
#include "asteroid.h"

LinkSignal &Asteroid::getController()
{
    return this->Controller;
}

void LinkSignal::destroy(int var)
{
    if (var == 1) {
        emit signalDestroy();
    }
    if (var == 2){
        emit signalEndGameMessage();
    }
}
