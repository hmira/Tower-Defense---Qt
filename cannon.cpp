#include "cannon.h"
#include <QVector2D>
#include <qmath.h>
#include <QDebug>

Cannon::Cannon()
{
}

Cannon::Cannon(QPixmap pixmap)
{
    this->original_pixmap = pixmap;
    this->pixmap = pixmap;
}

Cannon::Cannon(QPixmap pixmap, int x, int y)
{
    this->original_pixmap = pixmap;
    this->pixmap = pixmap;
    this->SizeX = this->SizeY = 64;
    this->hSizeX = this->hSizeY = 32;
    this->center.setX(x);
    this->center.setY(y);
    this->drawing_origin.setX(x - hSizeX);
    this->drawing_origin.setY(y - hSizeY);
    this->range = 120;
    this->shotinterval = 1000;
    this->lastshot = INT_MIN;
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

Bullet* Cannon::Shoot(Enemy *enemy, long elapsed)
{
    if (elapsed - lastshot < shotinterval) return 0;

    int xa = this->pixmap.size().width() - this->SizeX;
    int ya = this->pixmap.size().height() - this->SizeY;
    QVector2D tcenter(center.x() - xa * 0.5, center.y() - ya * 0.5);
    QVector2D target = GetInterSect(enemy->center, enemy->next_checkpoint,
                                    Bullet::speed, Enemy::speed,
                                    tcenter, enemy->center);
    if (target.isNull())
        target = GetInterSect2((enemy->center - enemy->next_checkpoint).length(),
                           enemy->next_checkpoint, enemy->next_checkpoint2,
                           Bullet::speed, Enemy::speed,
                           tcenter, enemy->center);

    if (target.isNull() || (this->center - target).length() > this->range)
        return 0;

    lastshot = elapsed;
    Bullet*b = new Bullet(tcenter, target, elapsed, QPixmap("bullet.png"));
    b->enemy = enemy;
    return b;
}

QVector2D Cannon::GetInterSect(const QVector2D Aa, const QVector2D Ba,
                          const float b_spd, const float e_spd,
                          const QVector2D b_pos, const QVector2D e_pos
                          )
{
    float Cann_dist1, Ball_dist1, Cann_dist2, Ball_dist2;
    QVector2D A = Aa;
    QVector2D B = Ba;

    while (true)
    {
        QVector2D C = (A + B) * 0.5;

        Cann_dist1 = (A - b_pos).length() * e_spd;
        Ball_dist1 = (A - e_pos).length() * b_spd;
        Cann_dist2 = (C - b_pos).length() * e_spd;
        Ball_dist2 = (C - e_pos).length() * b_spd;

        if (Ball_dist1 <= Cann_dist1 && Ball_dist2 >= Cann_dist2)
        {
            B = C;
            if (abs(Ball_dist1 - Ball_dist2) < 5)
            {
                return QVector2D(C.x(), C.y());
            }
            continue;
        }

        Cann_dist1 = Cann_dist2;
        Ball_dist1 = Ball_dist2;
        Cann_dist2 = (B - b_pos).length() * e_spd;
        Ball_dist2 = (B - e_pos).length() * b_spd;

        if (Ball_dist1 <= Cann_dist1 && Ball_dist2 >= Cann_dist2)
        {
            A = C;
            if (abs(Ball_dist1 - Ball_dist2) < 5)
            {
                return QVector2D(C.x(), C.y());
            }
            continue;
        }
        break;
    }
    return QVector2D();
}

QVector2D Cannon::GetInterSect2(float rmn,
                      const QVector2D Aa, const QVector2D Ba,
                      const float b_spd, const float e_spd,
                      const QVector2D b_pos, const QVector2D e_pos)
{
    float Cann_dist1, Ball_dist1, Cann_dist2, Ball_dist2;
    QVector2D A = Aa;
    QVector2D B = Ba;

    while (true)
    {
        QVector2D C = (A + B) * 0.5;

        Cann_dist1 = (A - b_pos).length() * e_spd;
        Ball_dist1 = ((A - e_pos).length() + rmn) * b_spd;
        Cann_dist2 = (C - b_pos).length() * e_spd;
        Ball_dist2 = ((C - e_pos).length() + rmn) * b_spd;

        if (Ball_dist1 <= Cann_dist1 && Ball_dist2 >= Cann_dist2)
        {
            B = C;
            if (abs(Ball_dist1 - Ball_dist2) < 5)
            {
                return QVector2D(C.x(), C.y());
            }
            continue;
        }

        Cann_dist1 = Cann_dist2;
        Ball_dist1 = Ball_dist2;
        Cann_dist2 = (B - b_pos).length() * e_spd;
        Ball_dist2 = ((B - e_pos).length() + rmn) * b_spd;

        if (Ball_dist1 <= Cann_dist1 && Ball_dist2 >= Cann_dist2)
        {
            A = C;
            if (abs(Ball_dist1 - Ball_dist2) < 5)
            {
                return QVector2D(C.x(), C.y());
            }
            continue;
        }
        break;
    }
    return QVector2D();
}
