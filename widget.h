#ifndef WIDGET_H
#define WIDGET_H

#include "enemyspaceship.h"
#include "spaceship.h"
#include "asteroid.h"

#include <QWidget>
#include <QPushButton>
#include <QTcpSocket>
#include <QLineEdit>
#include <QLabel>

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
    void showLeaders();
    void createMenu();
    void showMenu();
    void checkNickName();
    void slotDescriptionEndGame(QString textLine);
    void slotStopAnimationDestroySpaceships();
    void slotStartAnimationDestroySpaceships(int _enemySpaceShipX, int _enemySpaceShipY, int pixmapWidth, int pixmapHeight);
private:
    QString addToJson(QString str);
    QTcpSocket* m_pTcpSocket;
    quint16 m_nNextBlockSize;
    Asteroid* _asteroid;
    Spaceship* _spaceship;
    EnemySpaceship* _enemySpaceship;
    QLineEdit* lineEditName;
    QPushButton* buttonNewGame;
    QPushButton* buttonQuitGame;
    QPushButton* buttonLeaders;
    QPushButton* buttonBack;
    QGraphicsScene* scene;
    QGraphicsTextItem* score;
    QGraphicsTextItem* lose;
    QTimer* animationTimer;
    QTimer* generatorTimerAsteroid;
    QTimer* generatorTimerEnemySpaceship;
    QTimer* sceneHideTimer;
    QTimer* animationDestroyTimer;
    QTimer* moveEnemySpaceShipXTimer;
    QLabel* animationDestroyLabel;
    QMovie* destroyMovie;
    QGraphicsProxyWidget* proxy;
    bool endGame = true;
    bool startGame = true;
    int lastMapValue = 0;
    int _score = 0;
    int life = 3;
    int speedAsteroid= 2;
    int speedEnemySpaceship = 1;
    int moveEnemySpaceshipX = -1;
    int yLeadersLineStep = 100;
    int spaceshipsGetX();
    int spaceshipsGetY();
    void reinicializateEnemySpaceship();
    void connections();
    void hideMenu();
    void timers(bool startGame);
    void timersStart();
    void timersStop();
    void createSpaceship();
    void createScene();
    void clearScene();
    void descriptionScore(int size, QString fontType, QString textData, QColor textColor, int setPosX, int setPosY);
    void descriptionEndGame(int size, QString fontType, QString textData, QColor textColor, int setPosX, int setPosY);
    void insertDataReadyRead(QString str);
    void createNameLineEdit();
    void showYourScore();
protected:
    Ui::Widget *ui;
};

#endif // WIDGET_H
