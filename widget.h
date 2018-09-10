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
    void advance(int phase);
private:
    int yspeed;
};

class ex : public QObject {
    Q_OBJECT
public:
    ex(){}
    void destroy();
    void endGame();
signals:
    void signalDestroy();
    void signalEndGameMessage();
};

class Spaceship : public QGraphicsPixmapItem {
private:
    int xspeed = 0;
    ex ControllerEndGame;
    void endGameMessageSpaceship();
public:
    ex &getEndGameMessage();
    Spaceship(int sceneHeight);
    void advance(int phase);
protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
};

class Asteroid : public QGraphicsPixmapItem {
public:
    enum { Type = UserType + 1};
    Asteroid(int xspread);
    void advance(int phase);
    ex &getController();
    ex &getEndGameMessage();
    int type() const;
private:
    bool endGame = false;
    int yspeed = 2;
    ex Controller;
    ex ControllerEndGame;
    int test = 0;
    void sumTest();
    void endGameMessageAsteroid();
    void destroyAsteroidBullet();
    void destroyAsteroidRange();
};

class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
    static QGraphicsTextItem* text;
private slots:
    void onGenerate();
    void sumScore();
    void endGameMessage();
private:
    Ui::Widget *ui;
    QGraphicsScene* scene;
    QTimer* animationTimer;
    QTimer* generatorTimer;
    int _score = 0;
};

#endif // WIDGET_H
