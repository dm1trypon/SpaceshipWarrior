#include "const.h"

Asteroid::Asteroid(qreal xspread) : QGraphicsPixmapItem (nullptr)
{
    setPixmap(QPixmap(":/images/asteroid.png"));
    qreal post = rand() % static_cast<int>(xspread - pixmap().width());
    setPos(post, SCREEN_TOP);
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
