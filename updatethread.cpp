#include "updatethread.h"

// UpdateThread::UpdateThread(
//    std::map<std::string, QQueue<std::pair<double, double>>> *values,
//    std::map<std::string, std::string> *cmds,
//    std::map<std::string, int> *graphs, QCustomPlot *plt, QObject *parent)
//    : vals(values), plt(plt), cmds(cmds), graphs(graphs), QThread(parent)
//{
//}

UpdateThread::UpdateThread(DataModel *data, QObject *parent)
    : data(data), QThread(parent)
{
}

void UpdateThread::run()
{
    QProcess p;
    while (true) {
        auto cmd_pairs = this->data->getCommands();
        for (auto cmd_p = cmd_pairs.begin(); cmd_p != cmd_pairs.end();
             ++cmd_p) {
            std::string name = cmd_p->first;
            std::string command = cmd_p->second;

            p.start("bash", QStringList() << "-c"
                                          << QString::fromStdString(command));
            p.waitForFinished();
            QString output = p.readAllStandardOutput();

            this->data->addValue(name, output.toDouble());
            this->data->updateRange();
            p.kill();
        }
        this->data->getPlot()->replot();
        msleep(100);
    }
}
