#include "mainwidget.h"
#include <iostream>

MainWidget::MainWidget(QWidget *parent) : QWidget(parent)
{
    this->plot = new QCustomPlot();
    this->plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom
                                | QCP::iSelectPlottables);

    this->layout = new QBoxLayout(QBoxLayout::TopToBottom);
    QBoxLayout *vlayout = new QBoxLayout(QBoxLayout::LeftToRight);

    this->lineEdit = new QLineEdit();
    this->nameEdit = new QLineEdit();
    this->btn = new QPushButton("Watch!");
    this->clrbtn = new QPushButton("Clear");
    vlayout->addWidget(this->nameEdit);
    vlayout->addWidget(this->lineEdit);
    vlayout->addWidget(this->btn);
    vlayout->addWidget(this->clrbtn);

    layout->addLayout(vlayout);
    layout->addWidget(this->plot);
    this->setLayout(layout);

    connect(this->btn, SIGNAL(clicked(bool)), this, SLOT(addEntry(bool)));
    connect(this->clrbtn, SIGNAL(clicked(bool)), this, SLOT(clear(bool)));

    thread = new UpdateThread(&(this->values), &(this->commands),
                              &(this->graphs), this->plot);
    thread->start();
}

void MainWidget::addEntry(bool dunno)
{
    Q_UNUSED(dunno);

    std::string name = this->nameEdit->text().toStdString();
    std::string command = this->lineEdit->text().toStdString();

    if (name != "" && command != "") {
        if (this->values.find(name) != this->values.end()) {
            std::cout << "Error: name " << name << " already existing."
                      << std::endl;
        } else {
            this->values[name] = QQueue<std::pair<double, double>>();
            this->commands[name] = command;
            this->graphs[name] = this->plot->graphCount();
            this->plot->addGraph();
            this->plot->graph(this->plot->graphCount() - 1)
                ->setName(QString::fromStdString(name));
        }
    } else {
        std::cout << "Error: empty name for watchable" << std::endl;
    }

    this->lineEdit->setText("");
    this->nameEdit->setText("");
}

void MainWidget::clear(bool dunno)
{
    Q_UNUSED(dunno);
    this->values.clear();
    this->plot->clearItems();
    this->plot->replot();
}
