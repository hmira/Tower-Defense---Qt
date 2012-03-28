#ifndef CANNON_H
#define CANNON_H

#include <QPainter>
#include <QPixmap>
#include <QPoint>
#include <QVector2D>
#include <QTransform>

#include "bullet.h"
#include "enemy.h"

class Cannon
{
public:
    Cannon();
    Cannon(QPixmap pixmap);
    Cannon(QPixmap pixmap, int x, int y);

    void Update(int x, int y);
    void Draw(QPainter *painter);
    void Draw(QPainter *painter, int x, int y);
    void SetRotation(qreal r);
    void Aim(QVector2D pos);


    QPixmap original_pixmap;
    QPixmap pixmap;
    QPoint drawing_origin;
    QVector2D center;
    int SizeX, SizeY;
    int hSizeX, hSizeY;
    int range;
    QTransform transformation;
    Bullet * Shoot(Enemy enemy);

    QVector2D GetInterSect(  const QVector2D A,                //from
                        const QVector2D B,                //to
                        const float b_spd,         //speed of bullet
                        const float e_spd,          //speed of enemy
                        const QVector2D b_pos,  //position of bullet
                        const QVector2D e_pos   //position of enemy
                        );         //returns the intersection, if any
};

#endif // CANNON_H
