/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtGui>
#include "helper.h"

//! [0]
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

    //QLinearGradient gradient(QPointF(20, -20), QPointF(100, 180));
    //gradient.setColorAt(0.0, Qt::white);
    //gradient.setColorAt(1.0, Qt::blue);

    background = QBrush(QPixmap("/home/hmirap/qt_test2-build-desktop/bg.png"));
    //background = QBrush(QColor(64, 32, 64));
    circleBrush = QBrush(QPixmap("/home/hmirap/qt_test2/apple.png"));

    QPixmap qpapple("/home/hmirap/qt_test2/apple.png");

    for (int i = 0; i < 5; ++i) {
        enemies.push_back(new Enemy(qpapple, path, i*1000));
    }
}
//! [0]

//! [1]
void Helper::paint(QPainter *painter, QPaintEvent *event, long elapsed)
{
    painter->fillRect(event->rect(), background);
    //painter->translate(200, 200);
//! [1]

//! [2]
    painter->save();
    painter->setBrush(circleBrush);
    //painter->rotate(elapsed * 0.030);

    /*painter->drawPixmap( 1 * MapX + 45, 0 * MapY + 40, pixmap);
    painter->drawPixmap( 1 * MapX + 45, 1 * MapY + 40, pixmap);
    painter->drawPixmap( 1 * MapX + 45, 2 * MapY + 40, pixmap);
    painter->drawPixmap( 1 * MapX + 45, 3 * MapY + 40, pixmap);
    painter->drawPixmap( 1 * MapX + 45, 4 * MapY + 40, pixmap);*/



    for (int i = 0; i < enemies.size(); ++i) {
        enemies.at(i)->Move(elapsed);
        enemies.at(i)->Draw(painter);
    }
    //enemy->Draw(painter, 1 * MapX + 45, 0 * MapY + 40);

    //enemy.Update();


    qreal r = elapsed/1000.0;
    int n = 78;
    /*for (int i = 0; i < n; ++i) {
        painter->rotate(30);
        qreal radius = 0 + ((i+r));
        qreal circleRadius = 1 + ((i+r));
        painter->drawPixmap(radius * 3 + 20 , -circleRadius, pixmap);
        painter->drawEllipse(QRectF(radius * 3 + 20 , -circleRadius,
                                    circleRadius*0.6, circleRadius*0.6));
    }*/
    painter->restore();
//! [2]

}
