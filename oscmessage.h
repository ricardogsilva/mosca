#ifndef OSCMESSAGE_H
#define OSCMESSAGE_H

#include <QByteArray>
#include <QString>
#include <QList>
#include <QVariant>

class OscMessage
{
public:
    OscMessage(QByteArray* datagram);

    QString address();
    QList<QVariant> arguments();
    QString typeTags();

private:
    QString _address;
    QList<QVariant> _arguments;
};

#endif // OSCMESSAGE_H
