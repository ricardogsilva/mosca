#include <QCoreApplication>
#include <QString>
#include <QDebug>

#include "mosca.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug() << QString("Hello world!");
    Mosca mosca;
    return a.exec();
}
