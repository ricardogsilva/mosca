#include "mosca.h"
#include <QByteArray>
#include <QDebug>
#include <QBuffer>
#include <QDataStream>
#include <QIODevice>

#include "oscmessage.h"

Mosca::Mosca(QObject *parent) :
    QObject(parent)
{
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(5001, QUdpSocket::ShareAddress);

    connect(udpSocket, SIGNAL(readyRead()),
            this, SLOT(processPendingDatagrams()));
}

void Mosca::processPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size());
        OscMessage message = OscMessage(&datagram);
        qDebug() << "address: " << message.address();
        qDebug() << "arguments: " << message.arguments();
    }
}
