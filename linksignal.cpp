#include "const.h"

void LinkSignal::destroy(int var)
{
    switch (var) {
    case DESTROY:
        emit signalDestroy();
        break;
    case ENDGAME:
        emit signalEndGameMessage();
        break;
    case DESTROY_ENEMY_SPACESHIP:
    emit signalDestroyEnemySpaceship();
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
