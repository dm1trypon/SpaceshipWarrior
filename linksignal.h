#ifndef LINKSIGNAL_H
#define LINKSIGNAL_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsPixmapItem>
#include <QTimer>

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
};

#endif // LINKSIGNAL_H
