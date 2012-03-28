#include <QtGui>
#include <QTransform>
#include "helper.h"

Helper::Helper()
{

    MapX = 90;
    MapY = 80;
    this->path = new QList<QPoint*>();
    this->path->push_back(new QPoint(45 + 1 * MapX, 40 + 0 * MapY));
    this->path->push_back(new QPoint(45 + 1 * MapX, 40 + 4 * MapY));
    this->path->push_back(new QPoint(45 + 3 * MapX, 40 + 4 * MapY));
    this->path->push_back(new QPoint(45 + 3 * MapX, 40 + 1 * MapY));
    this->path->push_back(new QPoint(45 + 5 * MapX, 40 + 1 * MapY));
    this->path->push_back(new QPoint(45 + 5 * MapX, 40 + 4 * MapY));
    this->path->push_back(new QPoint(45 + 7 * MapX, 40 + 4 * MapY));
    this->path->push_back(new QPoint(45 + 7 * MapX, 40 + 1 * MapY));
    this->path->push_back(new QPoint(45 + 9 * MapX, 40 + 1 * MapY));
    this->path->push_back(new QPoint(45 + 9 * MapX, 40 + 6 * MapY));


    background = QBrush(QPixmap("bg.png"));

    this->qp_cannon = QPixmap("cannon.png");
    this->qp_bullet = QPixmap("bullet.png");
    this->qp_enemy = QPixmap("apple.png");

    for (int i = 0; i < 5; ++i) {
        enemies.push_back(new Enemy(this->qp_enemy, path, i*1000));
    }

    cannons.push_back(new Cannon(qp_cannon,4 * MapX + 45, 40 + 2 * MapY));
    cannons.push_back(new Cannon(qp_cannon,2 * MapX + 45, 40 + 3 * MapY));
    cannons.push_back(new Cannon(qp_cannon,6 * MapX + 45, 40 + 3 * MapY));

    this->bullet = new Bullet(QVector2D(10,10),QVector2D(620,320),1000,qp_bullet);

    QVector2D e;
    e = cannons.at(0)->GetInterSect(QVector2D(2,0), QVector2D(2,10),
                                1, 1,
                                QVector2D(-5,10), QVector2D(2,0));
}

void Helper::paint(QPainter *painter, QPaintEvent *event, long elapsed, QPoint focus)
{

    painter->fillRect(event->rect(), background);
    painter->save();

    if (!focus.isNull())
    {
        DrawHighlight(painter, focus);
    }

    //bullet->Move(elapsed);
    //bullet->Draw(painter);

    for (int i = 0; i < bullets.size(); ++i) {
        bullets.at(i)->Move(elapsed);
        bullets.at(i)->Draw(painter);
    }

    for (int i = 0; i < enemies.size(); ++i) {
        enemies.at(i)->Move(elapsed);
        enemies.at(i)->Draw(painter);
    }

    for (int i = 0; i < cannons.size(); ++i) {
        cannons.at(i)->Draw(painter);
        cannons.at(i)->Aim(enemies.at(0)->center);
    }

    if (elapsed % 10000 == 0 && elapsed != 0)
        enemies.pop_front();

    for (int i = 0; i < cannons.size(); ++i) {
        int j = 0;
        bool c = false;
        for (j = 0; j < enemies.size(); ++j) {
            if ((cannons.at(i)->center - enemies.at(j)->center).length() < cannons.at(i)->range)
            {
                c = true;
                Bullet* bullet1 = cannons.at(i)->Shoot(*enemies.at(j), elapsed);
                cannons.at(i)->Aim(enemies.at(j)->center);
                if (bullet1 != NULL)
                    bullets.push_back(bullet1);
                break;
            }
        }
        j = (j == enemies.size()) ? j-1:j;
        if (!c)
            this->cannons.at(i)->Aim(enemies.first()->center);
        else
            cannons.at(i)->Aim(enemies.at(j)->center);
    }

    painter->restore();
}

void Helper::DrawHighlight(QPainter *painter, QPoint pos)
{
    QPoint a(pos.x() - pos.x() % 90, pos.y() - pos.y() % 80 );
    painter->drawPixmap(a,QPixmap("high"));
}
