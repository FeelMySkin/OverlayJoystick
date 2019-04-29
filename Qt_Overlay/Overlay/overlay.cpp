#include "overlay.h"
#include "ui_overlay.h"
#include <QKeyEvent>
#include <qt_windows.h>

Overlay::Overlay(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Overlay)
{
    ui->setupUi(this);
    setWindowOpacity(9.0);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_ShowWithoutActivating);
    setWindowFlags( Qt::Window | Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowStaysOnTopHint | Qt::WindowDoesNotAcceptFocus | Qt::Tool | Qt::CustomizeWindowHint);

    HWND winHandle = (HWND)winId();
    SetWindowLongA(winHandle, GWL_EXSTYLE, GetWindowLongA(winHandle, GWL_EXSTYLE) | WS_EX_NOACTIVATE | WS_EX_APPWINDOW);

    connect(ui->pushButton,SIGNAL(pressed()),this,SLOT(PressF()));
    connect(ui->pushButton,SIGNAL(released()),this,SLOT(PressF()));
    connect(ui->checkBox,SIGNAL(clicked(bool)),this,SLOT(HoldShift(bool)));
}

void Overlay::PressF()
{
    if(ui->pushButton->isDown()) ui->label->setText("Pressed " + QVariant((++counter)).toString());
    else ui->label->setText("Released" + QVariant(--counter).toString());

    QKeyEvent *key_press = new QKeyEvent(QKeyEvent::KeyPress, Qt::Key_F, Qt::NoModifier, "FT");
    //QCoreApplication::sendEvent(nullptr,key_press);
    LPINPUT input = new INPUT();
    input->type = INPUT_KEYBOARD;
    input->ki.wScan = 0;
    input->ki.time = 0;
    input->ki.dwExtraInfo = 0;
    byte x = VkKeyScanA('f');
    input->ki.wVk = x;
    input->ki.wScan = 0x4B;
    if(ui->pushButton->isDown()) input->ki.dwFlags = 0;//KEYEVENTF_SCANCODE;
    else input->ki.dwFlags = KEYEVENTF_KEYUP;// | KEYEVENTF_SCANCODE;


    SendInput(1,input,sizeof(INPUT));
}

void Overlay::HoldShift(bool shift)
{
    LPINPUT input = new INPUT();
    input->type = INPUT_KEYBOARD;
    input->ki.wScan = 0;
    input->ki.time = 0;
    input->ki.dwExtraInfo = 0;
    byte x = VkKeyScanA('F');
    input->ki.wVk = VK_SHIFT;
    if(shift) input->ki.dwFlags = 0;
    else input->ki.dwFlags = KEYEVENTF_KEYUP;

    SendInput(1,input,sizeof(INPUT));
}

Overlay::~Overlay()
{
    delete ui;
}
