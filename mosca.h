#ifndef MOSCA_H
#define MOSCA_H

#include <QObject>
#include <QUdpSocket>

class Mosca : public QObject
{
    Q_OBJECT
public:
    explicit Mosca(QObject *parent = 0);

signals:

public slots:

private:
    QUdpSocket *udpSocket;

private slots:
    void processPendingDatagrams();
};

#endif // MOSCA_H
