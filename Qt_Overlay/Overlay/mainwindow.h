#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "overlay.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Overlay ovr;

private slots:
    void ShowOverlay(bool);
};

#endif // MAINWINDOW_H
