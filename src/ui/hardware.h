#ifndef HARDWARE_H
#define HARDWARE_H

#include <QObject>
//#include <QString>

class Hardware : public QObject
{
    Q_OBJECT
public:
    explicit Hardware(QObject* parent = nullptr);
    virtual ~Hardware();

    //Q_INVOKABLE void startI();
    Q_PROPERTY(bool isStarted READ isStarted)

    bool isStarted() const { return m_isStarted; }

public slots:
    void start();
    void stop();
    void restart();

signals:
    void message(const QString& msg);

private:
    void initDiskFromFile();
    void createTestDiskFile();
    void boot();
    void run();
    void getCurrentCommand();
    void execCurrentCommand();

private:
    // state
    bool m_isStarted;

    // registers
    quint32 m_PC;
    unsigned char* m_executedCommand;

    // memory
    unsigned char* m_memory;
    unsigned char* m_disk;
};

#endif // HARDWARE_H
