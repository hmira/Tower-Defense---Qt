#ifndef BULLET_H
#define BULLET_H
#include <QPoint>
#include <QVector2D>
#include <QPixmap>
#include <QPainter>

#include "enemy.h"

class Bullet
{
public:
    Bullet();
    Bullet(QVector2D from, QVector2D to, long spawned, QPixmap pixmap);
    void Move(long elapsed);
    void Draw(QPainter *painter);

    Enemy *enemy;
    QVector2D from, to, pos, direction;
    long spawned;
    int power;
    QPixmap pixmap;
    bool hitEnd;
    const static float speed = 0.4;
};

#endif // BULLET_H
