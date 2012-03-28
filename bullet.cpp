#include "bullet.h"

Bullet::Bullet()
{
}

Bullet::Bullet(QVector2D from, QVector2D to, long spawned, QPixmap pixmap)
{
    this->from = from;
    this->to = to;
    this->spawned = spawned;
    this->pixmap = pixmap;
    this->direction = to - from;
    this->direction.normalize();
    this->hitEnd = false;
    this->power =  5;
}

void Bullet::Move(long elapsed)
{
    float t = elapsed - this->spawned;
    this->pos = from + t * this->speed * direction;
    if ((pos - from).lengthSquared() > (to - from).lengthSquared())
        this->hitEnd = true;
}

void Bullet::Draw(QPainter *painter)
{
    if (!hitEnd)
        painter->drawPixmap(this->pos.x(), this->pos.y(), this->pixmap);
}
