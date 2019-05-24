#ifndef OVERLAY_H
#define OVERLAY_H

#include <QWidget>
#include <qt_windows.h>
#include <QTouchEvent>
#include "touchbutton.h"

namespace Ui {
class Overlay;
}

class Overlay : public QWidget
{
    Q_OBJECT

public:
    explicit Overlay(QWidget *parent = nullptr);
    ~Overlay();

private:
    Ui::Overlay *ui;
    uint16_t counter = 0;
    LPINPUT kb_input;
    TouchButton *btn;

private slots:
    void PressF();
    void GetSensorData(QPointF point, QTouchEvent *evt);
    void HoldShift(bool shift);
    void BringToTop();
};

#endif // OVERLAY_H
