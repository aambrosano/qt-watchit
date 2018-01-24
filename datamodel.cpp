#include "datamodel.h"

DataModel::DataModel(QObject *parent)
    : plot(new QCustomPlot()), use_mutex(new std::mutex()), QObject(parent)
{
    this->plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom
                                | QCP::iSelectPlottables);
    this->t.start();
}

DataModel::~DataModel() { delete this->plot; }

std::map<std::string, std::string> DataModel::getCommands()
{
    std::unique_lock<std::mutex>(*this->use_mutex);
    return this->commands;
}

void DataModel::setRange(double sec)
{
    std::unique_lock<std::mutex>(*this->use_mutex);
    Q_ASSERT(sec > 0);
    this->xrange = sec;
}

void DataModel::updateRange()
{
    std::unique_lock<std::mutex>(*this->use_mutex);
    double curr_t = t.elapsed() / 1000.0;
    this->plot->xAxis->setRange(curr_t - this->xrange, curr_t);
    this->plot->replot();
}

void DataModel::addValue(std::string name, double value)
{
    std::unique_lock<std::mutex>(*this->use_mutex);
    double curr_t = t.elapsed() / 1000.0;
    if (this->commands.find(name) == this->commands.end()) {
        std::cout << "Name " << name << " has been removed." << std::endl;
        return;
    }
    this->graphs[name]->addData(curr_t, value);
}
