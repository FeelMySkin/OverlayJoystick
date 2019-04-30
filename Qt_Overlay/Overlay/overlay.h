#ifndef OVERLAY_H
#define OVERLAY_H

#include <QWidget>
#include <qt_windows.h>

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

private slots:
    void PressF();
    void HoldShift(bool shift);
};

#endif // OVERLAY_H
