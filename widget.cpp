#include "spaceship.h"
#include "bullet.h"
#include "linksignal.h"
#include "asteroid.h"
#include "widget.h"
#include "ui_widget.h"
#include "enemyspaceship.h"
#include <QKeyEvent>
#include <QDebug>

QGraphicsTextItem* Widget::text;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(0, 0, 800, 600, this);
    scene->setStickyFocus(true);
    QPixmap pim(":/images/space.jpg");
    scene->setBackgroundBrush(pim.scaled(800,600,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    ui->graphicsView->setScene(scene);
    scene->addRect(scene->sceneRect());

    Spaceship* _spaceship = new Spaceship(scene->height());
    scene->addItem(new Spaceship(scene->height()));
    connect(&_spaceship->getController(), SIGNAL(signalEndGameMessage()), this, SLOT(endGameMessage()));


    animationTimer = new QTimer(this);
    connect(animationTimer, SIGNAL(timeout()),
            scene, SLOT(advance()));
    animationTimer->start(1000/60);

    generatorTimerAsteroid = new QTimer(this);
    connect(generatorTimerAsteroid, SIGNAL(timeout()),
            this, SLOT(onGenerateAsteroid()));

    generatorTimerEnemySpaceship = new QTimer(this);
    connect(generatorTimerEnemySpaceship, SIGNAL(timeout()),
            this, SLOT(onGenerateEnemySpaceship()));

    generatorTimerAsteroid->start(1000);

    generatorTimerEnemySpaceship->start(4500);

    QFont font;
    font.setPointSize(30);
    font.setFamily("Unispace");
    text = new QGraphicsTextItem;
    text = scene->addText(QString::number(0));
    text->setPos(0, -5);
    text->setDefaultTextColor(Qt::red);
    Widget::text->setFont(font);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::endGameMessage()
{
    if (endGame){
        QFont font_lose;
        font_lose.setPointSize(80);
        font_lose.setFamily("Unispace");
        QGraphicsTextItem *lose = new QGraphicsTextItem;
        lose = scene->addText("YOU LOSE!");
        lose->setPos(110, 210);
        lose->setFont(font_lose);
        lose->setDefaultTextColor(Qt::red);
        qDebug() << "End!";
        endGame = false;
        ui->graphicsView->hide();
        blockSignals(true);
    }
    qDebug() << "die!";
}

void Widget::onGenerateAsteroid()
{
    Asteroid* _asteroid = new Asteroid(scene->sceneRect().width());
    scene->addItem(_asteroid);
    connect(&_asteroid->getController(), SIGNAL(signalDestroy()), this, SLOT(sumScore()));
}

void Widget::onGenerateEnemySpaceship()
{
    EnemySpaceship* _enemySpaceship = new EnemySpaceship(scene->sceneRect().width());
    scene->addItem(_enemySpaceship);
    connect(&_enemySpaceship->getController(), SIGNAL(signalDestroy()), this, SLOT(sumScore()));
}

void Widget::sumScore()
{
    _score++;
    Widget::text->setPlainText(QString::number(_score));
    qDebug() << "score" << _score;
}



