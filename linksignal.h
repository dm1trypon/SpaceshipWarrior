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
public:
    LinkSignal(){}
    void destroy(int var);
    void endGame();
signals:
    void signalDestroy();
    void signalEndGameMessage();
};

#endif // LINKSIGNAL_H
