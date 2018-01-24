#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "datamodel.h"
#include "updatethread.h"
#include <QBoxLayout>
#include <QLineEdit>
#include <QProcess>
#include <QPushButton>
#include <QQueue>
#include <QWidget>

#include <iostream>
#include <map>
#include <string>

class MainWidget : public QWidget
{
    Q_OBJECT

private:
public:
    explicit MainWidget(QWidget *parent = nullptr);

signals:

public slots:
    void addEntry(bool dunno);
    void clear(bool dunno);

private:
    DataModel *data;
    QPushButton *clrbtn;
    QPushButton *btn;
    QBoxLayout *layout;
    QLineEdit *lineEdit;
    QLineEdit *nameEdit;
    UpdateThread *thread;
};

#endif // MAINWIDGET_H
