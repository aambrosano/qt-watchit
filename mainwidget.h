#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "qcustomplot.h"
#include <QBoxLayout>
#include <QLineEdit>
#include <QProcess>
#include <QPushButton>
#include <QQueue>
#include <QThread>
#include <QWidget>

#include <iostream>
#include <map>
#include <string>

class MainWidget : public QWidget
{
    Q_OBJECT

private:
    class UpdateThread : public QThread
    {
    public:
        UpdateThread(
            std::map<std::string, QQueue<std::pair<double, double>>> *values,
            std::map<std::string, std::string> *cmds,
            std::map<std::string, int> *graphs, QCustomPlot *plt,
            QObject *parent = nullptr)
            : vals(values), plt(plt), cmds(cmds), graphs(graphs),
              QThread(parent)
        {
        }

    protected:
        virtual void run() override
        {
            t.start();
            QProcess p;
            while (true) {
                std::cout << "count " << vals->size() << std::endl;
                for (auto x = vals->begin(); x != vals->end(); ++x) {
                    std::string name = x->first;
                    std::string command = this->cmds->operator[](name);
                    int graph = this->graphs->operator[](name);
                    p.start("bash", QStringList()
                                        << "-c"
                                        << QString::fromStdString(command));
                    p.waitForFinished();
                    std::cout << p.exitCode() << std::endl;
                    std::cout << p.errorString().toStdString() << std::endl;
                    std::cout << "(" << name << ") " << command << std::endl;
                    QString output = p.readAllStandardOutput();
                    std::cout << output.toStdString() << std::endl;
                    double el = t.elapsed() / 1000.;
                    this->plt->graph(graph)->addData(el, output.toDouble());
                    this->plt->xAxis->setRange(el - 5, el);

                    p.kill();
                }
                this->plt->replot();
                msleep(100);
            }
        }

    private:
        QCustomPlot *plt;
        std::map<std::string, QQueue<std::pair<double, double>>> *vals;
        std::map<std::string, std::string> *cmds;
        std::map<std::string, int> *graphs;
        QTime t;
    };

public:
    explicit MainWidget(QWidget *parent = nullptr);

signals:

public slots:
    void addEntry(bool dunno);
    void clear(bool dunno);

private:
    QCustomPlot *plot;
    QPushButton *clrbtn;
    QPushButton *btn;
    QBoxLayout *layout;
    QLineEdit *lineEdit;
    QLineEdit *nameEdit;
    UpdateThread *thread;
    std::map<std::string, QQueue<std::pair<double, double>>> values;
    std::map<std::string, std::string> commands;
    std::map<std::string, int> graphs;
};

#endif // MAINWIDGET_H
