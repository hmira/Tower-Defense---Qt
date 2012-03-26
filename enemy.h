#ifndef ENEMY_H
#define ENEMY_H

#include <QPixmap>
#include <QPoint>
#include <QVector2D>
#include <QPainter>

class Enemy
{
public:
    Enemy();
    Enemy(QPixmap pixmap);

    void Update(int x, int y);
    void Draw(QPainter *painter, int x, int y);
    void Draw(QPainter *painter);
    void Move(int elapsed);

    QPixmap pixmap;
    QPoint drawing_origin;
    QVector2D center;
    int SizeX, SizeY;
    int hSizeX, hSizeY;

    void setPath(QList<QPoint*> *path) {this->path = path;}

private:
    QList<QPoint*>* path;
};

#endif // ENEMY_H
