#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "overlay.h"
#include <QSystemTrayIcon>

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
    QSystemTrayIcon *tray;

private slots:
    void ShowOverlay(bool);
};

#endif // MAINWINDOW_H
