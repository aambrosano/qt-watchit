#include "mainwidget.h"
#include <iostream>

MainWidget::MainWidget(QWidget *parent) : QWidget(parent)
{
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

    this->data = new DataModel();
    this->thread = new UpdateThread(this->data);

    layout->addLayout(vlayout);
    layout->addWidget(this->data->getPlot());
    this->setLayout(layout);

    connect(this->btn, SIGNAL(clicked(bool)), this, SLOT(addEntry(bool)));
    connect(this->clrbtn, SIGNAL(clicked(bool)), this, SLOT(clear(bool)));

    this->thread->start();
}

void MainWidget::addEntry(bool dunno)
{
    Q_UNUSED(dunno);

    std::string name = this->nameEdit->text().toStdString();
    std::string command = this->lineEdit->text().toStdString();

    if (this->data->addCommand(name, command)) {
        this->lineEdit->setText("");
        this->nameEdit->setText("");
    }
}

void MainWidget::clear(bool dunno)
{
    Q_UNUSED(dunno);
    this->data->clear();
}
