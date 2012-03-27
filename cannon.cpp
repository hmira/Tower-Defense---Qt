#include "cannon.h"
#include <QVector2D>
#include <qmath.h>

Cannon::Cannon()
{
}

Cannon::Cannon(QPixmap pixmap)
{
    this->original_pixmap = pixmap;
    this->pixmap = pixmap;
}

void Cannon::Draw(QPainter *painter)
{
    QBrush qb(this->pixmap);
    this->pixmap = original_pixmap.transformed(this->transformation);
    int xa = this->pixmap.size().width() - this->SizeX;
    int ya = this->pixmap.size().height() - this->SizeY;
    painter->drawPixmap(this->drawing_origin.x() - xa / 2, this->drawing_origin.y() - ya / 2,this->pixmap);
    painter->setBrush(qb);
}

void Cannon::Draw(QPainter *painter, int x, int y)
{
    this->pixmap = original_pixmap.transformed(this->transformation);
    painter->drawPixmap(x,y,this->pixmap);
}

void Cannon::Update(int x, int y)
{
    this->SizeX = this->SizeY = 64;
    this->hSizeX = this->hSizeY = 32;
    this->center.setX(x);
    this->center.setY(y);
    this->drawing_origin.setX(x - hSizeX);
    this->drawing_origin.setY(y - hSizeY);
}

void Cannon::SetRotation(qreal r)
{
    r /= 100;
    QTransform t;

    QVector2D a(30,-3);

    a.normalize();

    //t.setMatrix(cos(r), -sin(r), 0, sin(r) , cos(r), 0, 0, 0, 1);
    t.setMatrix(a.y(), a.x(), 0, -a.x() , a.y(), 0, 0, 0, 1);

    this->transformation = t;
}

void Cannon::Aim(QVector2D pos)
{
    QVector2D vec(pos.x() - this->center.x(), this->center.y() - pos.y());
    QTransform t;
    vec.normalize();
    t.setMatrix(vec.y(), vec.x(), 0, -vec.x() , vec.y(), 0, 0, 0, 1);
    this->transformation = t;
}
