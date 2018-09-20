#include "asteroid.h"
#include "const.h"
#include "linksignal.h"

Asteroid::Asteroid(qreal xspread) : QObject(), QGraphicsPixmapItem (nullptr)
{
    this->setPixmap(QPixmap(":/images/asteroid.png"));
    srand(static_cast<uint>(time(nullptr)));
    setPos(getRandomWidth(xspread), SCREEN_TOP);
    connect(&LinkSignal::Instance(), SIGNAL(signalSpeedAsteroidSet(int)), this, SLOT(speedAsteroidSet(int)));
}

void Asteroid::speedAsteroidSet(int speedAsteroid)
{
    yspeed = speedAsteroid;
}

qreal Asteroid::getRandomWidth(qreal xspread)
{
    return rand() % static_cast<int>(xspread - pixmap().width());
}

void Asteroid::advance(int phase)
{
    if (phase <= 0) {
        return;
    }
    moveBy(0, yspeed);
    if (!onScreen()) {
        destroy(ENDGAME);
    }
    if (collision()) {
        destroy(DESTROY);
    }
}

bool Asteroid::collision()
{
    return data(0).toBool();
}

bool Asteroid::onScreen()
{
    return this->y() < SCREEN_HEIGHT + 200;
}

int Asteroid::type() const
{
    return Type;
}

void Asteroid::destroy(int var)
{
    switch (var)
    {
    case ENDGAME:
        LinkSignal::Instance().destroy(var);
        delete this;
        break;
    case DESTROY:
        LinkSignal::Instance().destroy(var);
        delete this;
        break;
    };
}
