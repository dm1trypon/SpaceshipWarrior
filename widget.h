#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>

#include "enemyspaceship.h"
#include "spaceship.h"
#include "asteroid.h"

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
    void lifeChangerEnemySpaceship();
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
    bool endGame = true;
    int _score = 0;
    int life = 3;
    void reinicializateEnemySpaceship();
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
};

#endif // WIDGET_H
