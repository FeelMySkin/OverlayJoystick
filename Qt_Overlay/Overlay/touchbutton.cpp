#include "touchbutton.h"
#include <QColor>
#include <QBrush>
#include <qt_windows.h>
#include <winuser.h>

TouchButton::TouchButton(QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_AcceptTouchEvents);
    ungrabGesture(Qt::GestureType::TapAndHoldGesture);
    painter = new QPainter(this);
    painter->setPen(QPen(Qt::red,1,Qt::SolidLine));
    painter->drawEllipse(0,0,50,50);

}

bool TouchButton::event(QEvent* event)
{
    switch(event->type())
    {
        case QEvent::TouchBegin:
        case QEvent::TouchUpdate:
        case QEvent::TouchEnd:
        {
            QTouchEvent *evt = static_cast<QTouchEvent*>(event);
            emit ReturnPosition(evt->touchPoints().first().pos(),evt);
            event->accept();
            return true;
        }

        default:
            return QWidget::event(event);
    }
}

void TouchButton::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QColor red("#ff0000");
    painter.setBrush(QBrush(red,Qt::SolidPattern));
    //painter.setPen(QPen(Qt::red,1,Qt::SolidPattern));
    painter.drawEllipse(0,0,this->width(),height());
    switch(event->type())
    {
        default:
        QWidget::paintEvent(event);
        break;
    }
}
