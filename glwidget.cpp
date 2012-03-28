#include <QtGui>
#include <QDebug>
#include "glwidget.h"
#include "helper.h"


GLWidget::GLWidget(Helper *helper, QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent), helper(helper)
{
    elapsed = 0;
    setFixedSize(990, 480);
    setAutoFillBackground(false);
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
    helper->paint(&painter, event, elapsed, focus);
    painter.end();
}

void GLWidget::mousePressEvent(QMouseEvent * event)
{
    this->focus = event->pos();
}


