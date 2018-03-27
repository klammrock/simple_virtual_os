#ifndef HARDWARETHREAD_H
#define HARDWARETHREAD_H

#include <QThread>

class HardwareThread : public QThread
{
    Q_OBJECT
public:
    explicit HardwareThread(QObject *parent = nullptr);
    ~HardwareThread();

    void stopRequest();

signals:

public slots:

    // QThread interface
protected:
    virtual void run() override;

private:
    volatile bool m_isStopRequest;
};

#endif // HARDWARETHREAD_H
