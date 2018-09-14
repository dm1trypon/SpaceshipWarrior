#ifndef CONST_H
#define CONST_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QDebug>
#include <QKeyEvent>
#include <QPushButton>

#include "asteroid.h"
#include "bullet.h"
#include "enemyspaceship.h"
#include "linksignal.h"
#include "spaceship.h"
#include "widget.h"

#define DESTROY 1
#define ENDGAME 2
#define DESTROY_ENEMY_SPACESHIP 3

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int SCREEN_TOP = -100;
const int SCREEN_WIDTH_END = 700;
const int SCREEN_WIDTH_BEGIN = -20;
const int LEFT = 0;
const int RIGHT = 1;
const int SEGMENT = 2;
const int TIME_ANIMATION = 1000;
const int TIME_GENERATION_ASTEROID = 1000;
const int TIME_GENERATION_ENEMY_SPACESHIP = 4500;
const int TIME_HIDE_SCENE = 2000;

#endif // CONST_H
