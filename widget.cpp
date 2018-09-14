#include "ui_widget.h"
#include "const.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    createScene();
    timers();
    createSpaceship();
    createMenu();
    scene->addRect(scene->sceneRect());
    connections();
    descriptionScore(30, "Unispace", QString::number(0), Qt::red, 0, -5);
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
    connect(sceneHideTimer, SIGNAL(timeout()), this, SLOT(stopGame()));
    connect(&LinkSignal::Instance(), SIGNAL(signalEndGameMessage()), this, SLOT(endGameMessage()));
    connect(&LinkSignal::Instance(), SIGNAL(signalDestroy()), this, SLOT(sumScore()));
    connect(&LinkSignal::Instance(), SIGNAL(signalDestroyEnemySpaceship()), this, SLOT(lifeChangerEnemySpaceship()));
    connect(buttonNewGame, SIGNAL(clicked()), this, SLOT(newGame()));
    connect(quitGame, SIGNAL(clicked()), this, SLOT(close()));
}

void Widget::createSpaceship()
{
    this->_spaceship = new Spaceship(scene->height());
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

void Widget::timers()
{
    animationTimer = new QTimer(this);
    generatorTimerAsteroid = new QTimer(this);
    generatorTimerEnemySpaceship = new QTimer(this);
    sceneHideTimer = new QTimer(this);
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
    if (!endGame) {
        return;
    }
    descriptionEndGame(80, "Unispace", "YOU LOSE!", Qt::yellow, 110, 210);
    endGame = false;
    sceneHideTimer->start(TIME_HIDE_SCENE);
}

void Widget::onGenerateAsteroid()
{
    this->_asteroid = new Asteroid(scene->sceneRect().width());
    scene->addItem(_asteroid);
}

void Widget::onGenerateEnemySpaceship()
{
    this->_enemySpaceship = new EnemySpaceship(scene->sceneRect().width());
    scene->addItem(_enemySpaceship);
}

void Widget::sumScore()
{
    _score++;
    score->setPlainText(QString::number(_score));
}

void Widget::createMenu()
{
    buttonNewGame = new QPushButton("New Game", this);
    buttonNewGame->setGeometry(QRect(QPoint(320, 100), QSize(200, 50)));
    quitGame = new QPushButton("Quit", this);
    quitGame->setGeometry(QRect(QPoint(320, 200), QSize(200, 50)));
    hideMenu();
}

void Widget::showMenu()
{
    buttonNewGame->show();
    quitGame->show();
}

void Widget::hideMenu()
{
    buttonNewGame->hide();
    quitGame->hide();
}

void Widget::stopGame()
{
    timersStop();
    clearScene();
    showMenu();
}

void Widget::newGame()
{
    blockSignals(false);
    endGame = true;
    _score = 0;
    hideMenu();
    timersStart();
    createSpaceship();
    scene->addRect(scene->sceneRect());
    descriptionScore(30, "Unispace", QString::number(0), Qt::red, 0, -5);
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
        delete this->_enemySpaceship;
        sumScore();
        return;
    }
    reinicializateEnemySpaceship();
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
