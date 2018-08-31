#include "widget.h"
#include "ui_widget.h"
#include <QKeyEvent>

#define CIRCLE_SIZE 50
#define SPACESHIP_SPEED 6
#define BULLET_LENGHT 10
#define BULLET_SPEED 4

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(0, 0, 800, 600, this);
    scene->setStickyFocus(true);
    scene->setBackgroundBrush(QBrush(Qt::black));
    QPixmap pim("E:/PROJECT/QT/animation-game/images/space.jpg");
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
}

Widget::~Widget()
{
    delete ui;
}

void Widget::onGenerate()
{
    scene->addItem(new Asteroid(scene->sceneRect().width()));
}

Asteroid::Asteroid(int xspread) : QGraphicsPixmapItem (0)
{
    setPixmap(QPixmap("E:/PROJECT/QT/animation-game/images/asteroid.png"));
    setPos(rand()%(xspread - pixmap().width()), 0);
}

void Asteroid::advance(int phase)
{
    if (phase) {
        moveBy(0, yspeed);
        if ((data(0).toBool()) || (Asteroid::y() > 800)) {
            delete this;
        }
    }
}

void Asteroid::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    delete this;
}

int Asteroid::type() const
{
    return Type;
}

Spaceship::Spaceship::Spaceship(int sceneHeight) : QGraphicsPixmapItem(0)
{
    setPixmap(QPixmap("E:/PROJECT/QT/animation-game/images/spaceship.png"));
    setPos(0, sceneHeight-pixmap().height());
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
}

void Spaceship::advance(int phase)
{
    if (!phase) {
        foreach(QGraphicsItem* item, collidingItems()) {
            Asteroid* obj = qgraphicsitem_cast<Asteroid*>(item);
            if (obj) {
                item->setData(0, true);
                setData(0, true);
            }
        }
    }
    else {
        if ((Spaceship::x() <= 700) && (Spaceship::x() >= -20)) {
            moveBy(xspeed, 0);
        }
        else {
            if ((Spaceship::x() >= 700)) {
                Spaceship::setPos(699, 600 - pixmap().height());
            }
            if ((Spaceship::x() <= -20)) {
                Spaceship::setPos(-19, 600 - pixmap().height());
            }
        }
        if (data(0).toBool()) {
            delete this;
        }
    }
}

void Spaceship::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Left:
        xspeed = - SPACESHIP_SPEED;
        break;
    case Qt::Key_Right:
        xspeed = SPACESHIP_SPEED;
        break;
    case Qt::Key_Space:
        scene()->addItem(new Bullet(mapToScene(QPointF(pixmap().width()/2, 0)), 0));
    default:
        break;
    }
}

void Spaceship::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Left:
        xspeed = 0;
        break;
    case Qt::Key_Right:
        xspeed = 0;
        break;
    default:
        break;
    }
}

Bullet::Bullet(QPointF initPos, QGraphicsItem *parent) : QGraphicsLineItem (parent)
{
    yspeed = BULLET_SPEED;
    setPen(QPen(QBrush(Qt::red), 3));
    setLine(0, 0, 0, -BULLET_LENGHT);
    setPos(initPos);
}

void Bullet::advance(int phase)
{
    if (!phase) {
        foreach(QGraphicsItem* item, collidingItems()) {
            Asteroid* obj = qgraphicsitem_cast<Asteroid*>(item);
            if (obj) {
                item->setData(0, true);
                setData(0, true);
            }
        }
    }
    else {
        moveBy(0, -yspeed);
        if (data(0).toBool() || (Bullet::y() < -100)) {
            delete this;
        }
    }
}
