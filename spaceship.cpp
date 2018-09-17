#include "const.h"

void Spaceship::endGameMessageSpaceship(int var)
{
    LinkSignal::Instance().destroy(var);
}

Spaceship::Spaceship::Spaceship() : QGraphicsPixmapItem(nullptr)
{
    setPixmap(QPixmap(":/images/spaceship.png"));
    setPos(SpaceshipPosX(), SpaceshipPosY());
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
}

qreal Spaceship::SpaceshipPosX()
{
    return SCREEN_WIDTH / 2 - pixmap().width() / 2;
}

qreal Spaceship::SpaceshipPosY()
{
    return SCREEN_HEIGHT - pixmap().height();
}

void Spaceship::advance(int phase)
{
    if (phase <= 0) {
        collisionObjects();
    }
    if (phase >= 1) {
        moveSpaceship();
    }
    if (collision()) {
        endGameMessageSpaceship(ENDGAME);
        delete this;
    }
}

void Spaceship::moveSpaceship()
{
    if (onWidthScreen(SEGMENT)) {
        moveBy(xspeed, 0);
    }
    if (!onWidthScreen(SEGMENT)) {
        stabilizeMoveSpaceship();
    }
}

void Spaceship::stabilizeMoveSpaceship()
{
    if (onWidthScreen(LEFT)) {
        this->setPos(SCREEN_WIDTH_END - 1, SCREEN_HEIGHT - 200 - pixmap().height());
    }
    if (onWidthScreen(RIGHT)) {
        this->setPos(SCREEN_WIDTH_BEGIN + 1, SCREEN_HEIGHT - 200 - pixmap().height());
    }
}

void Spaceship::collisionObjects()
{
    foreach(QGraphicsItem* item, collidingItems()) {
        Asteroid* objAsteroid = qgraphicsitem_cast<Asteroid*>(item);
        EnemySpaceship* objEnemySpaceship = qgraphicsitem_cast<EnemySpaceship*>(item);
        destroyDefinition(item, objAsteroid, objEnemySpaceship);
    }
}

void Spaceship::destroyDefinition(QGraphicsItem* item, Asteroid* objAsteroid, EnemySpaceship* objEnemySpaceship)
{
    if (objectDefinition(objAsteroid, objEnemySpaceship)) {
        item->setData(0, true);
        setData(0, true);
    }
}

bool Spaceship::objectDefinition(Asteroid* objAsteroid, EnemySpaceship* objEnemySpaceship)
{
    return objAsteroid || objEnemySpaceship;
}

bool Spaceship::onWidthScreen(int var)
{
    switch (var) {
    case 0:
        return this->x() >= SCREEN_WIDTH_END;
    case 1:
        return this->x() <= SCREEN_WIDTH_BEGIN;
    case 2:
        return this->x() >= SCREEN_WIDTH_BEGIN && this->x() <= SCREEN_WIDTH_END;
    default:
        return false;
    }
}

bool Spaceship::collision()
{
    return data(0).toBool();
}

void Spaceship::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Left:
        xspeed = - spaceshipSpeed;
        break;
    case Qt::Key_Right:
        xspeed = spaceshipSpeed;
        break;
    case Qt::Key_Space:
        scene()->addItem(new Bullet(mapToScene(QPointF(pixmap().width()/2, 0)), nullptr));
        break;
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
