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

    for (int i = 0; i < 10; ++i) {
        enemies.push_back(new Enemy(this->qp_enemy, path, i*1000));
    }

    for (int i = 0; i < 10; ++i) {
        enemies.push_back(new Enemy(this->qp_enemy, path, 13000 + i*1000));
    }

    this->bullet = new Bullet(QVector2D(10,10),QVector2D(620,320),1000,qp_bullet);

    this->money = 0;
    this->gameresult = 0;
}

void Helper::paint(QPainter *painter, QPaintEvent *event, long elapsed, QPoint focus, QList<Cannon*> cannons)
{

    painter->fillRect(event->rect(), background);
    painter->save();

    if (!focus.isNull())
    {
        DrawHighlight(painter, focus);
    }

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
        if (!enemies.empty()) cannons.at(i)->Aim(enemies.at(0)->center);
    }

    for (int i = 0; i < cannons.size(); ++i) {
        int j = 0;
        bool c = false;
        for (j = 0; j < enemies.size(); j++) {
            if ((cannons.at(i)->center - enemies.at(j)->center).length() < cannons.at(i)->range)
            {
                c = true;
                Bullet* bullet1 = cannons.at(i)->Shoot(enemies.at(j), elapsed);
                cannons.at(i)->Aim(enemies.at(j)->center);
                if (bullet1 != NULL)
                    bullets.push_back(bullet1);
                break;
            }
        }

        if (!enemies.empty())
        {
            if (!c)
                cannons.at(i)->Aim(enemies.first()->center);
            else
                cannons.at(i)->Aim(enemies.at(j)->center);
        }
    }

    for (int i = 0; i < bullets.size(); ++i) {
        Bullet* b = bullets.at(i);
        if (bullets.at(i)->hitEnd)
        {
            if (enemies.contains(b->enemy))
                b->enemy->Hit(b->power);
            delete bullets.at(i);
            bullets.removeAt(i);
        }
    }

    for (int i = 0; i < enemies.size(); ++i){
        Enemy* e = enemies.at(i);
        if (e->Strength < 1)
        {
            this->money++;
            enemies.removeOne(e);
            delete e;
        }
    }

    if (enemies.empty())
    {
        this->gameresult = 1;
    }
    else
    {
        if (enemies.at(0)->next_checkpoint == enemies.at(0)->next_checkpoint2 &&  enemies.at(0)->center.y() > 480)
            this->gameresult = 2;
    }

    painter->restore();
}

void Helper::DrawHighlight(QPainter *painter, QPoint pos)
{
    QPoint a(pos.x() - pos.x() % 90, pos.y() - pos.y() % 80 );
    painter->drawPixmap(a,QPixmap("high"));
}
