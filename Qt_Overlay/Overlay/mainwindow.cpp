#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCheckBox>
#include <QMenu>
#include <QStyle>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tray = new QSystemTrayIcon(this);
    tray->setToolTip("Overlay");
    tray->setIcon(this->style()->standardIcon(QStyle::SP_ComputerIcon));

    QMenu * menu = new QMenu(this);

    QAction *overlay_start = new QAction("Start Overlay",this);
    overlay_start->setCheckable(true);
    QAction *exit_prog = new QAction("Exti",this);
    overlay_start->

    connect(ui->checkBox,SIGNAL(clicked(bool)),this,SLOT(ShowOverlay(bool)));
    connect(overlay_start,SIGNAL(triggered(bool)),this,SLOT(ShowOverlay(bool)));
    connect(exit_prog,SIGNAL(triggered()),this,SLOT(close()));

    menu->addAction(overlay_start);
    menu->addAction(exit_prog);
    tray->setContextMenu(menu);
    tray->show();

    QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::MessageIcon(QSystemTrayIcon::Information);

    tray->showMessage("Tray Program",
                          trUtf8("Приложение свернуто в трей. Для того чтобы, "
                                 "развернуть окно приложения, щелкните по иконке приложения в трее"),
                          icon,
                          2000);
    this->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ShowOverlay(bool status)
{
    this->hide();
    if(status ) ovr.show();
    else ovr.hide();
}
