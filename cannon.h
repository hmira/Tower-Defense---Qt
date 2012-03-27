#ifndef CANNON_H
#define CANNON_H

#include <QPainter>
#include <QPixmap>
#include <QPoint>
#include <QVector2D>
#include <QTransform>

class Cannon
{
public:
    Cannon();
    Cannon(QPixmap pixmap);

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
    QTransform transformation;

};

#endif // CANNON_H
