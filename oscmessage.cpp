#include "oscmessage.h"

#include <QDebug>
#include <QBuffer>

OscMessage::OscMessage(QByteArray* datagram)
{
    int addressSize = datagram->indexOf('\0');
    int paddedAddressSize = addressSize;
    if (addressSize % 4 != 0) {
        paddedAddressSize = addressSize + (4 - addressSize % 4);
    }
    int extraAddressBytes = paddedAddressSize - addressSize;
    int typeTagsSize = datagram->indexOf('\0', addressSize);
    int paddedTypeTagsSize = typeTagsSize;
    if (typeTagsSize % 4 != 0) {
        paddedTypeTagsSize = typeTagsSize + (4 - typeTagsSize % 4);
    }
    int extraTypeTagsBytes = paddedTypeTagsSize - typeTagsSize;
    int argumentsSize = datagram->size() - (paddedAddressSize + paddedTypeTagsSize);
    QBuffer buffer;
    buffer.setBuffer(datagram);
    buffer.open(QIODevice::ReadOnly);
    _address = QString(buffer.read(addressSize));
    buffer.read(extraAddressBytes);
    QByteArray typeTags = buffer.read(typeTagsSize);
    buffer.read(extraTypeTagsBytes);
    QDataStream stream(&buffer);
    foreach (char theType, typeTags) {
        if (theType == 'i') {
            qint32 argument;
            stream >> argument;
            _arguments.append(QVariant(argument));
        } else if (theType == 'f') {
            float argument;
            stream >> argument;
            _arguments.append(QVariant(argument));
        } else if (theType == 's') {
            int stringEnd = datagram->indexOf('\0', buffer.pos());
            QString argument;
            int extraBytes = 0;
            if (stringEnd % 4 != 0) {
                extraBytes = 4 - stringEnd % 4;
            }
            argument = QString(buffer.read(stringEnd - buffer.pos()));
            buffer.read(extraBytes);
            _arguments.append(QVariant(argument));
        }
    }
    buffer.close();
}

QString OscMessage::address() {
    return _address;
}

QString OscMessage::typeTags() {
    return QString(1);
}

QList<QVariant> OscMessage::arguments() {
    return _arguments;
}
