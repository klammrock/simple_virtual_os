#include "hardware.h"

#include <QDebug>

Hardware::Hardware(QObject* parent) : QObject(parent)
{

}

void Hardware::startI()
{
    qDebug() << "startI";
    emit message("startI");
}

void Hardware::start()
{
    qDebug() << "start";
    emit message("start");
}
