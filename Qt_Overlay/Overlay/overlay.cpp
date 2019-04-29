#include "overlay.h"
#include "ui_overlay.h"

Overlay::Overlay(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Overlay)
{
    ui->setupUi(this);
    setWindowOpacity(9.0);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_TransparentForMouseEvents);
    setWindowFlags(Qt::WindowDoesNotAcceptFocus);
    //setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::WindowDoesNotAcceptFocus);
}

Overlay::~Overlay()
{
    delete ui;
}
