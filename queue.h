#ifndef QUEUE_H
#define QUEUE_H

#include <QObject>

class Queue : public QObject
{
    Q_OBJECT
public:
    explicit Queue(std::string &tag, std::string &desc = "",
                   QObject *parent = nullptr);

signals:

public slots:
};

#endif // QUEUE_H
