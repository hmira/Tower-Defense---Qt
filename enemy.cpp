#include "enemy.h"
#include <QDebug>

Enemy::Enemy()
{
    this->SizeX = this->SizeY = 35;
    this->hSizeX = this->hSizeY = 17;
    pixmap = *new QPixmap("/home/hmirap/qt_test2/apple.png");
    this->spawned = 1;
    this->speed = 0.15f;
}


Enemy::Enemy(QPixmap pixmap)
{
    this->spawned = 1;
    this->speed = 0.15f;
    this->SizeX = this->SizeY = 35;
    this->hSizeX = this->hSizeY = 17;
    this->pixmap = pixmap;
}


void Enemy::Update(int x, int y)
{
    this->center.setX(x);
    this->center.setY(y);
    this->drawing_origin.setX(x - hSizeX);
    this->drawing_origin.setY(y - hSizeY);
}

void Enemy::Draw(QPainter *painter, int x, int y)
{
    this->Update(x, y);
    painter->drawPixmap(this->drawing_origin, this->pixmap);
}

void Enemy::Draw(QPainter *painter)
{
    painter->drawPixmap(this->drawing_origin, this->pixmap);
}

void Enemy::Move(long elapsed)
{
    float lap = (elapsed - spawned) * this->speed;
        for (int i = 0; i < this->path->size() - 1; ++i)
        {
            QPoint q = *this->path->at(i + 1) - *this->path->at(i);

            int length = q.manhattanLength();

            if (lap > length)
                lap -= length;
            else
            {
                float e = (float)lap / length;
                QPoint new_point = *this->path->at(i) + e * q;
                this->Update(new_point.x(), new_point.y());
                return;
            }
        }
}
