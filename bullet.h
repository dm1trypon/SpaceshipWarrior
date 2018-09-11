#ifndef BULLET_H
#define BULLET_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsPixmapItem>
#include <QTimer>

class Bullet : public QGraphicsLineItem{
public:
    Bullet(QPointF initPos, QGraphicsItem* parent);
    void advance(int phase);
private:
    int yspeed;
};

#endif // BULLET_H
