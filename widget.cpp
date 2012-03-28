#include <QtGui>
#include "widget.h"
#include "helper.h"


Widget::Widget(Helper *helper, QWidget *parent)
    : QWidget(parent), helper(helper)
{
    elapsed = 0;
    setFixedSize(990, 480);
}


void Widget::animate()
{
    elapsed = (elapsed + qobject_cast<QTimer*>(sender())->interval());
    repaint();
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    helper->paint(&painter, event, elapsed);
    painter.end();
}
