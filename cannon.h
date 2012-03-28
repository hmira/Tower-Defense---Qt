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
    long lastshot;
    int shotinterval;
    QTransform transformation;
    Bullet * Shoot(Enemy enemy, long elapsed);

    QVector2D GetInterSect(  const QVector2D A,                //from
                        const QVector2D B,                //to
                        const float b_spd,         //speed of bullet
                        const float e_spd,          //speed of enemy
                        const QVector2D b_pos,  //position of bullet
                        const QVector2D e_pos);   //position of enemy

    QVector2D GetInterSect2( float rmn,             //lenght of track to next checkpoint
                        const QVector2D A,                //from
                        const QVector2D B,                //to
                        const float b_spd,         //speed of bullet
                        const float e_spd,          //speed of enemy
                        const QVector2D b_pos,  //position of bullet
                        const QVector2D e_pos);   //position of enemy

};

#endif // CANNON_H
