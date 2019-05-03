#ifndef TOUCHBUTTON_H
#define TOUCHBUTTON_H

#include <QWidget>
#include <QPainter>
#include <QPen>
#include <QPointF>
#include <QEvent>
#include <QPaintEvent>
#include <QTouchEvent>

class TouchButton : public QWidget
{
    Q_OBJECT
public:
    explicit TouchButton(QWidget *parent = nullptr);

private:
    QPainter *painter;
    bool event(QEvent* event);
    void paintEvent(QPaintEvent *event);

signals:
    void ReturnPosition(QPointF, QTouchEvent*);

public slots:
};

#endif // TOUCHBUTTON_H
