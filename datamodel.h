#ifndef DATAMODEL_H
#define DATAMODEL_H

#include "qcustomplot.h"
#include <QObject>
#include <QQueue>
#include <iostream>
#include <memory>
#include <mutex>

class DataModel : public QObject
{
    Q_OBJECT
public:
    explicit DataModel(QObject *parent = nullptr);
    ~DataModel();

    bool addCommand(std::string name, std::string command)
    {
        std::unique_lock<std::mutex>(*this->use_mutex);
        if (std::find(this->names.begin(), this->names.end(), name)
            != this->names.end()) {
            std::cout << "Name " << name
                      << " already existing, please choose another name."
                      << std::endl;
            return false;
        }

        this->commands[name] = command;
        this->plot->addGraph();
        this->graphs[name] = this->plot->graph(this->plot->graphCount() - 1);
    }

    QCustomPlot *getPlot() { return this->plot; }

    void clear()
    {
        std::unique_lock<std::mutex>(*this->use_mutex);

        this->names.clear();
        this->values.clear();
        this->commands.clear();
        this->graphs.clear();
        this->plot->clearGraphs();
    }

    std::map<std::string, std::string> getCommands();

    void setRange(double sec);

    void updateRange();

    void addValue(std::string name, double value);

signals:

public slots:

private:
    QCustomPlot *plot;
    std::vector<std::string> names;
    std::map<std::string, std::vector<std::pair<double, double>>> values;
    std::map<std::string, std::string> commands;
    std::map<std::string, QCPGraph *> graphs;
    std::shared_ptr<std::mutex> use_mutex;

    double xrange = 60.0; // 60 seconds by default
    QTime t;
    //    void addGraph(std::string name);
    //    void getGraph(std::string name);

    //    void addValue(std::string name, std::pair<double, double> value)
    //    {
    //        std::unique_lock<std::mutex>(*this->use_mutex);

    //        Q_ASSERT(this->values.find(name) != this->values.end());
    //        this->values[name].push_back(value);
    //    }
};

#endif // DATAMODEL_H
