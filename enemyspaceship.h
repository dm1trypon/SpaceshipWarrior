#ifndef ENEMYSPACESHIP_H
#define ENEMYSPACESHIP_H

#include <QGraphicsPixmapItem>

class EnemySpaceship : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    enum { Type = UserType + 2};
    EnemySpaceship(qreal xspread);
    void advance(int phase);
    int type() const;
private slots:
    void speedEnemySpaceshipSet(int speedEnemySpace);
private:
    bool check = true;
    int yspeed = 1;
    int xspeed = 0;
    bool change = false;
    bool onScreen();
    bool collision();
    void destroy(int var); 
    int changeXspeed(int xspeed);
    qreal getRandomWidth(qreal xspread);
};


#endif // ENEMYSPACESHIP_H
