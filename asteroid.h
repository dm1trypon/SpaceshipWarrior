#ifndef ASTEROID_H
#define ASTEROID_H

#include <QGraphicsPixmapItem>
#include <QMovie>

class Asteroid : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    enum { Type = UserType + 1};
    Asteroid(qreal xspread);
    void advance(int phase);
    int type() const;
private slots:
    void speedAsteroidSet(int speedGame);
private:
    QMovie destroyAnimation;
    int yspeed = 2;
    bool collision();
    bool onScreen();
    qreal getRandomWidth(qreal xspread);
    void destroy(int var);
};
#endif // ASTEROID_H
