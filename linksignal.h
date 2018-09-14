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
    static LinkSignal& Instance();
signals:
    void signalDestroy();
    void signalEndGameMessage();
    void signalDestroyEnemySpaceship();
};

#endif // LINKSIGNAL_H
