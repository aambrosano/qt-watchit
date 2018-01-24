#ifndef UPDATETHREAD_H
#define UPDATETHREAD_H

#include "datamodel.h"
#include <QThread>
#include <qcustomplot.h>

class UpdateThread : public QThread
{
    Q_OBJECT

public:
    UpdateThread(DataModel *data, QObject *parent = nullptr);

protected:
    virtual void run() override;

private:
    DataModel *data;
};

#endif // UPDATETHREAD_H
