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


    background = QBrush(QPixmap("/home/hmirap/qt_test2-build-desktop/bg.png"));

    QPixmap qpapple("/home/hmirap/qt_test2/apple.png");;

    this->qp_cannon = QPixmap("cannon.png");
    this->qp_bullet = QPixmap("bullet.png");
    this->qp_enemy = QPixmap("apple.png");

    for (int i = 0; i < 5; ++i) {
        enemies.push_back(new Enemy(qpapple, path, i*1000));
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

void Helper::paint(QPainter *painter, QPaintEvent *event, long elapsed)
{
    painter->fillRect(event->rect(), background);
    painter->save();

    for (int i = 0; i < enemies.size(); ++i) {
        enemies.at(i)->Move(elapsed);
        enemies.at(i)->Draw(painter);
    }

    for (int i = 0; i < cannons.size(); ++i) {
        cannons.at(i)->Aim(enemies.at(0)->center);
        cannons.at(i)->Draw(painter);
    }

    bullet->Move(elapsed);
    bullet->Draw(painter);

    if (elapsed % 10000 == 0 && elapsed != 0)
        enemies.pop_front();

    qreal r = elapsed/1000.0;
    int n = 78;
    painter->restore();
}
