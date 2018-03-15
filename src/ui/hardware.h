#ifndef HARDWARE_H
#define HARDWARE_H

#include <QObject>
//#include <QString>

class Hardware : public QObject
{
    Q_OBJECT
public:
    explicit Hardware(QObject* parent = nullptr);

    Q_INVOKABLE void startI();

public slots:
    void start();

signals:
    void message(const QString& msg);
};

#endif // HARDWARE_H
