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

    cannons.push_back(new Cannon(qp_cannon,4 * MapX + 45, 40 + 2 * MapY));
    cannons.push_back(new Cannon(qp_cannon,2 * MapX + 45, 40 + 3 * MapY));
    cannons.push_back(new Cannon(qp_cannon,6 * MapX + 45, 40 + 3 * MapY));
}


void GLWidget::animate()
{
    elapsed = (elapsed + qobject_cast<QTimer*>(sender())->interval());
    repaint();
}


void GLWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    helper->paint(&painter, event, elapsed, focus, this->cannons);
    painter.end();
}

void GLWidget::mousePressEvent(QMouseEvent * event)
{
    this->focus = event->pos();
}

void GLWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    cannons.push_back(new Cannon(qp_cannon, event->x() - event->x() % MapX + 45, event->y() - event->y() % MapY + 40));
}
