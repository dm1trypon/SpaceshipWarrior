#include "linksignal.h"
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

//void LinkSignal::setMoveEnemySpaceshipX(int moveEnemySpaceshipX)
//{
//    emit signalSetMoveEnemySpaceshipX(moveEnemySpaceshipX);
//}

void LinkSignal::descriptionEndGame(QString textLine)
{
    emit signalDescriptionEndGame(textLine);
}

void LinkSignal::getScore(int score)
{
    emit signalGetScore(score);
}

void LinkSignal::getLineEditText(QString lineEditText)
{
    emit signalLineEditText(lineEditText);
}

void LinkSignal::endGameCheck(bool endGame)
{
    emit signalEndGameCheck(endGame);
}

void LinkSignal::sendToServerGet()
{
    emit signalSendToServerGet();
}

void LinkSignal::sendToServerSet()
{
    emit signalSendToServerSet();
}

void LinkSignal::speedEnemySpaceshipSet(int speedEnemySpaceShip)
{
    emit signalSpeedEnemySpaceshipSet(speedEnemySpaceShip);
}

void LinkSignal::speedAsteroidSet(int speedAsteroid)
{
    emit signalSpeedAsteroidSet(speedAsteroid);
}

LinkSignal &LinkSignal::Instance()
{
    static LinkSignal theSingleInstance;
    return theSingleInstance;
}
