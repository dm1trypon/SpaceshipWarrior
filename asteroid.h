#ifndef ASTEROID_H
#define ASTEROID_H

#include <QGraphicsPixmapItem>

#include "linksignal.h"

class Asteroid : public QGraphicsPixmapItem
{
public:
    enum { Type = UserType + 1};
    Asteroid(qreal xspread);
    void advance(int phase);
    int type() const;
private:
    int yspeed = 2;
    bool collision();
    bool onScreen();
    void destroy(int var);
};
#endif // ASTEROID_H
