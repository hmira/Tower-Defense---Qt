#include "enemy.h"

Enemy::Enemy()
{
    this->SizeX = this->SizeY = 35;
    this->hSizeX = this->hSizeY = 17;
    pixmap = *new QPixmap("/home/hmirap/qt_test2/apple.png");
}


Enemy::Enemy(QPixmap pixmap)
{
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