#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>

#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsPixmapItem>

#include <QTimer>

namespace Ui {
class Widget;
}

class Bullet : public QGraphicsLineItem{
public:
    Bullet(QPointF initPos, QGraphicsItem* parent);
private:
    int yspeed;


    // QGraphicsItem interface
public:
    void advance(int phase);
};

class Spaceship : public QGraphicsPixmapItem {
public:
    Spaceship(int sceneHeight);

    // QGraphicsItem interface
public:
    void advance(int phase);

protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
private:
    int xspeed = 0;
};

class Asteroid : public QGraphicsPixmapItem {
public:
    enum { Type = UserType + 1};
    Asteroid(int xspread);

    // QGraphicsItem interface
public:
    void advance(int phase);
private:
    int yspeed = 2;

    // QGraphicsItem interface
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    // QGraphicsItem interface
public:
    int type() const;
};


class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
private slots:
    void onGenerate();
private:
    Ui::Widget *ui;
    QGraphicsScene* scene;
    QTimer* animationTimer;
    QTimer* generatorTimer;
};

#endif // WIDGET_H
