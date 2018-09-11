#include "spaceship.h"
#include "bullet.h"
#include "linksignal.h"
#include "asteroid.h"
#include "widget.h"
#include "ui_widget.h"
#include <QKeyEvent>
#include <QDebug>

#define CIRCLE_SIZE 50
#define SPACESHIP_SPEED 6
#define BULLET_LENGHT 10
#define BULLET_SPEED 4

QGraphicsTextItem* Widget::text;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(0, 0, 800, 600, this);
    scene->setStickyFocus(true);
    //scene->setBackgroundBrush(QBrush(Qt::black));
    QPixmap pim(":/images/space.jpg");
    scene->setBackgroundBrush(pim.scaled(800,600,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    ui->graphicsView->setScene(scene);
    scene->addRect(scene->sceneRect());
    scene->addItem(new Spaceship(scene->height()));

    animationTimer = new QTimer(this);
    connect(animationTimer, SIGNAL(timeout()),
            scene, SLOT(advance()));
    animationTimer->start(1000/60);

    generatorTimer = new QTimer(this);
    connect(generatorTimer, SIGNAL(timeout()),
            this, SLOT(onGenerate()));
    generatorTimer->start(1000);
    QFont f;
    f.setPointSize(30);
    f.setFamily("Unispace");
    text = new QGraphicsTextItem;
    text = scene->addText(QString::number(0));
    text->setPos(0, -5);
    text->setDefaultTextColor(Qt::red);
    Widget::text->setFont(f);
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
        blockSignals(true);
    }
}

void Widget::onGenerate()
{
    Asteroid* _asteroid = new Asteroid(scene->sceneRect().width());
    scene->addItem(_asteroid);
    connect(&_asteroid->getController(), SIGNAL(signalDestroy()), this, SLOT(sumScore()));
    connect(&_asteroid->getController(), SIGNAL(signalEndGameMessage()), this, SLOT(endGameMessage()));
    //disconnect(&_asteroid->getController(), SIGNAL(signalEndGameMessage()), this, SLOT(endGameMessage()));
}

void Widget::sumScore()
{
    _score++;
    Widget::text->setPlainText(QString::number(_score));
    qDebug() << "score" << _score;
}



