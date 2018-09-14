#ifndef ENEMYSPACESHIP_H
#define ENEMYSPACESHIP_H

#include <QGraphicsPixmapItem>

class EnemySpaceship : public QGraphicsPixmapItem
{
public:
    enum { Type = UserType + 2};
    EnemySpaceship(qreal xspread);
    void advance(int phase);
    int type() const;
private:
    bool check = true;
    int yspeed = 3;
    int xspeed = 0;
    bool change = false;
    bool onScreen();
    bool collision();
    void destroy(int var);
    int changeXspeed(int xspeed);
};


#endif // ENEMYSPACESHIP_H
