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

#define DESTROY 1
#define ENDGAME 2

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
    static QGraphicsTextItem* text;
private slots:
    void onGenerateAsteroid();
    void onGenerateEnemySpaceship();
    void sumScore();
    void endGameMessage();
private:
    bool endGame = true;
    Ui::Widget *ui;
    QGraphicsScene* scene;
    QTimer* animationTimer;
    QTimer* generatorTimerAsteroid;
    QTimer* generatorTimerEnemySpaceship;
    int _score = 0;
};

#endif // WIDGET_H
