#include <QtGui>
#include "glwidget.h"
#include "widget.h"
#include "window.h"

//! [0]
Window::Window()
    : QWidget()
{
    this->setFixedSize(1050,500);
    GLWidget *glw = new GLWidget(&helper, this);
    //Widget *native = new Widget(&helper, this);
    //QLabel *nativeLabel = new QLabel(tr("Native"));
    //nativeLabel->setAlignment(Qt::AlignHCenter);

    QGridLayout *layout = new QGridLayout;
    layout->setAlignment(Qt::AlignCenter);
    //layout->addWidget(native, 0, 0);
    //layout->addWidget(nativeLabel, 1, 0);

    layout->addWidget(glw, 0, 0);
    //layout->addWidget(native, 0, 0);
    setLayout(layout);

    QTimer *timer = new QTimer(this);
    //connect(timer, SIGNAL(timeout()), native, SLOT(animate()));
    connect(timer, SIGNAL(timeout()), glw, SLOT(animate()));
    timer->start(50);

    setWindowTitle(tr("2D Painting on Native and OpenGL Widgets"));
}
//! [0]
