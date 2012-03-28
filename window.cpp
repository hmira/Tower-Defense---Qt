#include <QtGui>
#include <stdio.h>
#include "glwidget.h"
#include "widget.h"
#include "window.h"

Window::Window()
    : QWidget()
{
    this->setFixedSize(1050,560);
    glw = new GLWidget(&helper, this);
    money = new QLabel(tr("Money:"));
    //Widget *native = new Widget(&helper, this);
    //QLabel *nativeLabel = new QLabel(tr("Native"));
    //nativeLabel->setAlignment(Qt::AlignHCenter);

    QGridLayout *layout = new QGridLayout;
    layout->setAlignment(Qt::AlignCenter);
    //layout->addWidget(native, 0, 0);
    //layout->addWidget(nativeLabel, 1, 0);

    layout->addWidget(glw, 0, 0);
    layout->addWidget(money);
    //layout->addWidget(native, 0, 0);
    setLayout(layout);

    timer = new QTimer(this);
    //connect(timer, SIGNAL(timeout()), native, SLOT(animate()));
    connect(timer, SIGNAL(timeout()), glw, SLOT(animate()));

    connect(glw, SIGNAL(updateMoney()), this, SLOT(SetMoneyLabel()));

    connect(glw, SIGNAL(gameOver()) , this, SLOT(EndGame()));

    timer->start(30);

    setWindowTitle(tr("Tower defense"));
}

void Window::SetMoneyLabel()
{
    char str[30];
    sprintf(str, "Money is:%d", glw->money);
    this->money->setText(str);
}

void Window::EndGame()
{
    this->timer->stop();
}
