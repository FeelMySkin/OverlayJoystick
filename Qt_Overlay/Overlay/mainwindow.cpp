#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCheckBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->checkBox,SIGNAL(clicked(bool)),this,SLOT(ShowOverlay(bool)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ShowOverlay(bool status)
{
    if(status ) ovr.show();
    else ovr.hide();
}
