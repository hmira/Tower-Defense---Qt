#include <QtGui>
#include <QDebug>
#include <QPixmap>
#include "glwidget.h"
#include "helper.h"


GLWidget::GLWidget(Helper *helper, QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent), helper(helper)
{
    elapsed = 0;
    setFixedSize(990, 480);
    setAutoFillBackground(false);

    MapX = 90; MapY = 80;
    qp_cannon = QPixmap("cannon.png");

    for (int i = 0; i < 11; ++i) {
        for (int j = 0; j < 6; ++j) {
            this->map[i][j] = false;
        }
    }

    for (int i = 0; i < 5; ++i) {
        this->map[0][i] = true;
    }

    for (int i = 2; i < 11; ++i) {
        this->map[i][0] = true;
    }

    for (int i = 1; i < 6; ++i) {
        this->map[10][i] = true;
    }

    for (int i = 0; i < 9; ++i) {
        this->map[i][5] = true;
    }

    for (int i = 0; i < 3; ++i) {
        this->map[2][i+1] = true;
    }

    for (int i = 0; i < 3; ++i) {
        this->map[6][i+1] = true;
    }

    for (int i = 0; i < 3; ++i) {
        this->map[4][i+2] = true;
    }

    for (int i = 0; i < 3; ++i) {
        this->map[8][i+2] = true;
    }

    this->money = 5;
}


void GLWidget::animate()
{
    if (helper->gameresult == 1)
    {
        gameOverW();
        return;
    }
    else if (helper->gameresult == 2)
    {
        gameOverL();
        return;
    }
    elapsed = (elapsed + qobject_cast<QTimer*>(sender())->interval());
    repaint();
}


void GLWidget::paintEvent(QPaintEvent *event)
{
    helper->money = this->money;
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    helper->paint(&painter, event, elapsed, focus, this->cannons);
    painter.end();
    this->money = helper->money;
    updateMoney();
}

void GLWidget::mousePressEvent(QMouseEvent * event)
{
    int x = event->x() / MapX;
    int y = event->y() / MapY;
    if (map[x][y])
        this->focus = event->pos();
}

void GLWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    int x = event->x() / MapX;
    int y = event->y() / MapY;
    if (map[x][y] == 1 && money > 0)
    {
        cannons.push_back(new Cannon(qp_cannon, event->x() - event->x() % MapX + 45, event->y() - event->y() % MapY + 40));
        money--;
        map[x][y] = 2;
    }
}

