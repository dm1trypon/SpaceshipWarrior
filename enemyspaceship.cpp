#include "const.h"

EnemySpaceship::EnemySpaceship(qreal xspread) : QGraphicsPixmapItem (nullptr)
{
    setPixmap(QPixmap(":/images/spaceship-big.png"));
    qreal post = rand() % static_cast<int>(xspread - pixmap().width());
    setPos(post, SCREEN_TOP);
}

void EnemySpaceship::advance(int phase)
{
    if (phase <= 0) {
        return;
    }
    moveBy(xspeed, yspeed);

    if (!onScreen()) {
        destroy(ENDGAME);
    }

    if (collision()) {
        destroy(DESTROY_ENEMY_SPACESHIP);
    }
}

bool EnemySpaceship::collision()
{
    return data(0).toBool();
}

bool EnemySpaceship::onScreen()
{
    return this->y() < SCREEN_HEIGHT + 200;
}

void EnemySpaceship::destroy(int var)
{
    switch (var)
    {
    case ENDGAME:
        LinkSignal::Instance().destroy(var);
        delete this;
        break;
    case DESTROY_ENEMY_SPACESHIP:
        LinkSignal::Instance().destroy(var);
        break;
    };
}

int EnemySpaceship::type() const
{
    return Type;
}
