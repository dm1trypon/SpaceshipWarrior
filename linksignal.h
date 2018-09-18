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
    void destroy(int var);
    void descriptionEndGame(QString textLine);
    void getScore(int score);
    void getLineEditText(QString lineEditText);
    void endGameCheck(bool endGame);
    void sendToServerGet();
    void sendToServerSet();
    static LinkSignal& Instance();
signals:
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
