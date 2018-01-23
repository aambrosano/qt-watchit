#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mainwidget.h"
#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    MainWidget *widget;
};

#endif // MAINWINDOW_H
