#ifndef WIDGET_H
#define WIDGET_H

#include "enemyspaceship.h"
#include "spaceship.h"
#include "asteroid.h"

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QPushButton>

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
private slots:
    void onGenerateAsteroid();
    void onGenerateEnemySpaceship();
    void sumScore();
    void endGameMessage();
    void newGame();
    void stopGame();
private:
    Asteroid* _asteroid;
    Spaceship* _spaceship;
    EnemySpaceship* _enemySpaceship;
    QPushButton* buttonNewGame;
    QPushButton* quitGame;
    QGraphicsScene* scene;
    QGraphicsTextItem* score;
    QGraphicsTextItem* lose;
    QTimer* animationTimer;
    QTimer* generatorTimerAsteroid;
    QTimer* generatorTimerEnemySpaceship;
    QTimer* sceneHideTimer;
    const uint TIME_ANIMATION = 1000;
    const int TIME_GENERATION_ASTEROID = 1000;
    const int TIME_GENERATION_ENEMY_SPACESHIP = 4500;
    const int TIME_HIDE_SCENE = 3000;
    const int SCREEN_HEIGHT = 600;
    const int SCREEN_WIDTH = 800;
    bool endGame = true;
    int _score = 0;
    void connections();
    void showMenu();
    void hideMenu();
    void createMenu();
    void timers();
    void timersStart();
    void timersStop();
    void createSpaceship();
    void createScene();
    void clearScene();
    void descriptionScore(int size, QString fontType, QString textData, QColor textColor, int setPosX, int setPosY);
    void descriptionEndGame(int size, QString fontType, QString textData, QColor textColor, int setPosX, int setPosY);
protected:
    Ui::Widget *ui;
//    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // WIDGET_H
