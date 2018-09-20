#include "ui_widget.h"
#include "const.h"
#include "widget.h"
#include "linksignal.h"

#include <QTimer>
#include <QGraphicsProxyWidget>
#include <QWidget>
#include <QKeyEvent>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QFile>
#include <QStringList>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    createScene();
    timers(startGame);
    createNameLineEdit();
    startGame = false;
    createMenu();
    hideMenu();
    connections();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::connections()
{
    connect(animationTimer, SIGNAL(timeout()), scene, SLOT(advance()));
    connect(generatorTimerAsteroid, SIGNAL(timeout()), this, SLOT(onGenerateAsteroid()));
    connect(generatorTimerEnemySpaceship, SIGNAL(timeout()), this, SLOT(onGenerateEnemySpaceship()));
    connect(animationDestroyTimer, SIGNAL(timeout()), this, SLOT(slotStopAnimationDestroySpaceships()));
    connect(sceneHideTimer, SIGNAL(timeout()), this, SLOT(stopGame()));
    connect(&LinkSignal::Instance(), SIGNAL(signalEndGameMessage()), this, SLOT(endGameMessage()));
    connect(&LinkSignal::Instance(), SIGNAL(signalDestroy()), this, SLOT(sumScore()));
    connect(&LinkSignal::Instance(), SIGNAL(signalDestroyEnemySpaceship()), this, SLOT(lifeChangerEnemySpaceship()));
    connect(&LinkSignal::Instance(), SIGNAL(signalDescriptionEndGame(QString)), this, SLOT(slotDescriptionEndGame(QString)));
    connect(buttonNewGame, SIGNAL(clicked()), this, SLOT(newGame()));
    connect(buttonLeaders, SIGNAL(clicked()), this, SLOT(showLeaders()));
    connect(buttonQuitGame, SIGNAL(clicked()), this, SLOT(close()));
    connect(buttonBack, SIGNAL(clicked()), this, SLOT(showMenu()));
    connect(lineEditName, SIGNAL(returnPressed()), this, SLOT(checkNickName()));
}

void Widget::createSpaceship()
{
    this->_spaceship = new Spaceship();
    scene->addItem(_spaceship);
}

void Widget::createScene()
{
    scene = new QGraphicsScene(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, this);
    scene->setStickyFocus(true);
    QPixmap pim(":/images/space.jpg");
    scene->setBackgroundBrush(pim.scaled(SCREEN_WIDTH, SCREEN_HEIGHT, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    ui->graphicsView->setScene(scene);
}

void Widget::timers(bool startGame)
{
    animationTimer = new QTimer(this);
    animationDestroyTimer = new QTimer(this);
    generatorTimerAsteroid = new QTimer(this);
    generatorTimerEnemySpaceship = new QTimer(this);
    sceneHideTimer = new QTimer(this);
    if (startGame)
    {
        return;
    }
    timersStart();
}

void Widget::timersStart()
{
    animationTimer->start(TIME_ANIMATION/60);
    generatorTimerAsteroid->start(TIME_GENERATION_ASTEROID);
    generatorTimerEnemySpaceship->start(TIME_GENERATION_ENEMY_SPACESHIP);
}

void Widget::timersStop()
{
    sceneHideTimer->stop();
    animationTimer->stop();
    generatorTimerAsteroid->stop();
    generatorTimerEnemySpaceship->stop();
}
void Widget::descriptionScore(int size, QString fontType, QString textData, QColor textColor, int setPosX, int setPosY)
{
    QFont fontScore;
    fontScore.setPointSize(size);
    fontScore.setFamily(fontType);
    score = new QGraphicsTextItem;
    score = scene->addText(textData);
    score->setPos(setPosX, setPosY);
    score->setDefaultTextColor(textColor);
    score->setFont(fontScore);
}

void Widget::descriptionEndGame(int size, QString fontType, QString textData, QColor textColor, int setPosX, int setPosY)
{
    QFont fontLose;
    fontLose.setPointSize(size);
    fontLose.setFamily(fontType);
    lose = new QGraphicsTextItem;
    lose = scene->addText(textData);
    lose->setPos(setPosX, setPosY);
    lose->setDefaultTextColor(textColor);
    lose->setFont(fontLose);
}

void Widget::endGameMessage()
{
    if (!endGame)
    {
        return;
    }
    descriptionEndGame(80, "Unispace", "YOU LOSE!", Qt::yellow, 110, 210);
    endGame = false;
    LinkSignal::Instance().endGameCheck(endGame);
    if(this->_spaceship != nullptr)
    {
        slotStartAnimationDestroySpaceships(static_cast<int>(this->_spaceship->x()), static_cast<int>(this->_spaceship->y()), this->_spaceship->pixmap().width(), this->_spaceship->pixmap().height());
        scene->removeItem(this->_spaceship);
    }
    sceneHideTimer->start(TIME_HIDE_SCENE);
}

void Widget::onGenerateAsteroid()
{
    this->_asteroid = new Asteroid(scene->sceneRect().width());
    scene->addItem(_asteroid);
    LinkSignal::Instance().speedAsteroidSet(speedAsteroid);
}

void Widget::onGenerateEnemySpaceship()
{
    this->_enemySpaceship = new EnemySpaceship(scene->sceneRect().width());
    scene->addItem(_enemySpaceship);
    LinkSignal::Instance().speedEnemySpaceshipSet(speedEnemySpaceShip);
}

void Widget::sumScore()
{
    _score++;
    LinkSignal::Instance().getScore(_score);
    if (_score % 20 == 0)
    {
        speedAsteroid++;
        speedEnemySpaceShip++;
        LinkSignal::Instance().speedAsteroidSet(speedAsteroid);
        LinkSignal::Instance().speedEnemySpaceshipSet(speedEnemySpaceShip);
    }
    score->setPlainText(QString::number(_score));
}

void Widget::checkNickName()
{
    if (lineEditName->text() == "")
    {
        return;
    }
    LinkSignal::Instance().getLineEditText(lineEditName->text());
    showMenu();
}

void Widget::slotDescriptionEndGame(QString textLine)
{
    descriptionEndGame(25, "Unispace", textLine, Qt::yellow, 280, yLeadersLineStep += 30);
}

void Widget::createNameLineEdit()
{
    lineEditName = new QLineEdit("", this);
    lineEditName->setMaxLength(15);
    lineEditName->setPlaceholderText("Insert your nickname...");
    lineEditName->setStyleSheet("font: 25px");
    lineEditName->setGeometry(QRect(QPoint(250, 275), QSize(300, 50)));
}

void Widget::createMenu()
{
    buttonNewGame = new QPushButton("New Game", this);
    buttonNewGame->setGeometry(QRect(QPoint(350, 100), QSize(200, 50)));
    buttonLeaders = new QPushButton("Leaders", this);
    buttonLeaders->setGeometry(QRect(QPoint(350, 200), QSize(200, 50)));
    buttonQuitGame = new QPushButton("Quit", this);
    buttonQuitGame->setGeometry(QRect(QPoint(350, 300), QSize(200, 50)));
    buttonBack = new QPushButton("Back", this);
    buttonBack->setGeometry(QRect(QPoint(350, 50), QSize(200, 50)));
}

void Widget::showLeaders()
{
    endGame = true;
    LinkSignal::Instance().endGameCheck(endGame);
    hideMenu();
    buttonBack->show();
    LinkSignal::Instance().sendToServerGet();
}

void Widget::showMenu()
{
    lineEditName->hide();
    buttonNewGame->show();
    buttonLeaders->show();
    buttonQuitGame->show();
    buttonBack->hide();
    clearScene();
    descriptionEndGame(25, "Unispace", "Hello, " + lineEditName->text(), Qt::cyan, 250, 10);
    yLeadersLineStep = 100;
}

void Widget::hideMenu()
{
    buttonNewGame->hide();
    buttonLeaders->hide();
    buttonQuitGame->hide();
    buttonBack->hide();
    clearScene();
}

void Widget::stopGame()
{
    buttonBack->hide();
    LinkSignal::Instance().sendToServerSet();
    timersStop();
    clearScene();
    showMenu();
}

void Widget::newGame()
{
    blockSignals(false);
    endGame = true;
    LinkSignal::Instance().endGameCheck(endGame);
    _score = 0;
    hideMenu();
    timersStart();
    createSpaceship();
    scene->addRect(scene->sceneRect());
    descriptionScore(30, "Unispace", QString::number(0), Qt::darkCyan, 0, -5);
}

void Widget::clearScene()
{
    QList<QGraphicsItem*> list = scene->items();
    for(int i = 0; i < list.length(); i++)
    {
        scene->removeItem(list[i]);
    }
    blockSignals(true);
}

void Widget::lifeChangerEnemySpaceship()
{
    if (!life)
    {
        life = 3;
        slotStartAnimationDestroySpaceships(spaceshipsGetX(), spaceshipsGetY(), this->_enemySpaceship->pixmap().width(), this->_enemySpaceship->pixmap().height());
        delete this->_enemySpaceship;
        sumScore();
        return;
    }
    reinicializateEnemySpaceship();
}

void Widget::slotStopAnimationDestroySpaceships()
{
    destroyMovie->stop();
    animationDestroyTimer->stop();
}

void Widget::slotStartAnimationDestroySpaceships(int _enemySpaceShipX, int _enemySpaceShipY, int pixmapWidth, int pixmapHeight)
{
    animationDestroyLabel = new QLabel();
    animationDestroyLabel->setGeometry(QRect(QPoint(_enemySpaceShipX, _enemySpaceShipY), QSize(pixmapWidth, pixmapHeight)));
    destroyMovie = new QMovie(":/images/destroy.gif");
    proxy = scene->addWidget(animationDestroyLabel);
    animationDestroyLabel->setAttribute(Qt::WA_NoSystemBackground);
    animationDestroyLabel->setMovie(destroyMovie);
    proxy->setWidget(animationDestroyLabel);
    destroyMovie->setScaledSize(QSize(pixmapWidth, pixmapHeight));
    animationDestroyTimer->start(TIME_ANIMATION);
    destroyMovie->start();
}

int Widget::spaceshipsGetX()
{
    return static_cast<int>(this->_enemySpaceship->x());
}

int Widget::spaceshipsGetY()
{
    return static_cast<int>(this->_enemySpaceship->y());
}

void Widget::reinicializateEnemySpaceship()
{
    qreal x = this->_enemySpaceship->x();
    qreal y = this->_enemySpaceship->y();
    delete this->_enemySpaceship;
    onGenerateEnemySpaceship();
    this->_enemySpaceship->setPos(x, y);
    life--;
}
