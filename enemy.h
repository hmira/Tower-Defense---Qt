#ifndef ENEMY_H
#define ENEMY_H

#include <QPixmap>
#include <QPoint>
#include <QVector2D>

class Enemy
{
public:
    Enemy();
    Enemy(QPixmap pixmap);

    void Update(int x, int y);

    QPixmap pixmap;
    QPoint drawing_origin;
    QVector2D center;
    int SizeX, SizeY;
    int hSizeX, hSizeY;

};

#endif // ENEMY_H
