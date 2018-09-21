#ifndef LINKSIGNAL_H
#define LINKSIGNAL_H

#include <QWidget>

class LinkSignal : public QObject {
    Q_OBJECT

private:
    LinkSignal(){}
    LinkSignal(const LinkSignal& root) = delete;
    LinkSignal& operator=(const LinkSignal&) = delete;

public:
    //void setMoveEnemySpaceshipX(int moveEnemySpaceshipX);
    void destroyAsteroid();
    void destroy(int var);
    void descriptionEndGame(QString textLine);
    void getScore(int score);
    void getLineEditText(QString lineEditText);
    void endGameCheck(bool endGame);
    void sendToServerGet();
    void sendToServerSet();
    void speedEnemySpaceshipSet(int speedEnemySpaceShip);
    void speedAsteroidSet(int speedAsteroid);
    static LinkSignal& Instance();
signals:
    //void signalSetMoveEnemySpaceshipX(int moveEnemySpaceshipX);
    void signalDestroyAsteroid();
    void signalSpeedAsteroidSet(int speedAsteroid);
    void signalSpeedEnemySpaceshipSet(int speedEnemySpaceship);
    void signalDestroy();
    void signalEndGameCheck(bool endGame);
    void signalLineEditText(QString lineEditText);
    void signalEndGameMessage();
    void signalDestroyEnemySpaceship();
    void signalDescriptionEndGame(QString textLine);
    void signalGetScore(int score);
    void signalSendToServerGet();
    void signalSendToServerSet();
};

#endif // LINKSIGNAL_H
