#include "overlay.h"
#include "ui_overlay.h"
#include <QKeyEvent>
#include <QDesktopWidget>
#include <QScreen>
#include <QPushButton>
#include <QTouchEvent>

Overlay::Overlay(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Overlay)
{
    ui->setupUi(this);
    setWindowOpacity(9.0);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_ShowWithoutActivating);
    setAttribute(Qt::WA_AcceptTouchEvents);
    ui->Right->setAttribute(Qt::WA_AcceptTouchEvents);
    setWindowFlags( Qt::Window | Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowStaysOnTopHint | Qt::WindowDoesNotAcceptFocus | Qt::Tool | Qt::CustomizeWindowHint);
    this->setGeometry(0,0,QGuiApplication::primaryScreen()->geometry().width(),QGuiApplication::primaryScreen()->geometry().height());
    HWND winHandle = (HWND)winId();
    SetWindowLongA(winHandle, GWL_EXSTYLE, GetWindowLongA(winHandle, GWL_EXSTYLE) | WS_EX_NOACTIVATE | WS_EX_APPWINDOW);

    connect(ui->Left,SIGNAL(pressed()),this,SLOT(PressF()));
    connect(ui->Right,SIGNAL(pressed()),this,SLOT(PressF()));
    connect(ui->Left,SIGNAL(released()),this,SLOT(PressF()));
    connect(ui->Right,SIGNAL(released()),this,SLOT(PressF()));
    connect(ui->checkBox,SIGNAL(clicked(bool)),this,SLOT(HoldShift(bool)));

    ungrabGesture(Qt::GestureType::TapAndHoldGesture);
    kb_input = new INPUT();
    kb_input->type = INPUT_KEYBOARD;
    kb_input->ki.wScan = 0;
    kb_input->ki.time = 0;
    kb_input->ki.dwExtraInfo = 0;
    kb_input->ki.wScan = 0x4B;
}

void Overlay::PressF()
{
    QPushButton *obj = (QPushButton*)sender();

    if(obj->isDown()) kb_input->ki.dwFlags = 0;//KEYEVENTF_SCANCODE;
    else kb_input->ki.dwFlags = KEYEVENTF_KEYUP;// | KEYEVENTF_SCANCODE;

    if(obj == ui->Right)
    {
        kb_input->ki.wVk = VK_RIGHT;
    }
    if(obj == ui->Left)
    {
        kb_input->ki.wVk = VK_LEFT;
    }


    SendInput(1,kb_input,sizeof(INPUT));
}

void Overlay::HoldShift(bool shift)
{

    LPINPUT input = new INPUT();
    input->type = INPUT_KEYBOARD;
    input->ki.wScan = 0;
    input->ki.time = 0;
    input->ki.dwExtraInfo = 0;
    input->ki.wVk = VK_SHIFT;
    if(shift) input->ki.dwFlags = 0;
    else input->ki.dwFlags = KEYEVENTF_KEYUP;

    SendInput(1,input,sizeof(INPUT));
}

Overlay::~Overlay()
{
    delete ui;
}

bool Overlay::event(QEvent *event)
{
    switch(event->type())
    {
        case QEvent::TouchBegin:
        case QEvent::TouchUpdate:
        case QEvent::TouchEnd:
        {
            QTouchEvent *tch = static_cast<QTouchEvent*>(event);
            QList<QTouchEvent::TouchPoint> points;
            event->accept();
            return true;
            break;
        }

        case QEvent::Gesture:
        {
            event->accept();
            return true;
        }

        default:
            return QWidget::event(event);
        break;
    }
}
