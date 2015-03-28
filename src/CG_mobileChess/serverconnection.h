#ifndef SERVERCONNECTION_H
#define SERVERCONNECTION_H

#include <QObject>

class serverConnection : public QObject
{
    Q_OBJECT
public:
    explicit serverConnection(QObject *parent = 0);
    ~serverConnection();

signals:

public slots:
};

#endif // SERVERCONNECTION_H
