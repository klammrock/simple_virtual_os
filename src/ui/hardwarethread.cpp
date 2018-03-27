#include "hardwarethread.h"
#include <QDebug>

HardwareThread::HardwareThread(QObject *parent) :
    QThread(parent),
    m_isStopRequest(false)
{
    qDebug() << "HardwareThread: ctor";
}

HardwareThread::~HardwareThread()
{
    qDebug() << "HardwareThread dtor";
}

void HardwareThread::stopRequest()
{
    m_isStopRequest = true;
}

void HardwareThread::run()
{
    m_isStopRequest = false;
    qDebug() << "HardwareThread::run()" << QThread::currentThreadId();
    //exec();

    int i = 3;

    while (i--) {
        if (m_isStopRequest)
            break;
        qDebug() << "work" << i;
        sleep(1);
    }

    qDebug() << "HardwareThread after exec";
}
