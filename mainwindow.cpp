#include "mainwindow.h"
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    this->widget = new MainWidget();
    this->setCentralWidget(this->widget);
    this->setWindowState(Qt::WindowMaximized);
}

MainWindow::~MainWindow() {}
