#ifndef HARDWARE_H
#define HARDWARE_H

#include <QObject>
#include <QHash>
#include <QThread>

class Hardware;
// function for optable
typedef void (Hardware::*opfunc)();

class HardwareThread;

class Hardware : public QThread
{
    Q_OBJECT
public:
    explicit Hardware(QObject* parent = nullptr);
    virtual ~Hardware();

    //Q_INVOKABLE void startI();
    Q_PROPERTY(bool isStarted READ isStarted)

    bool isStarted() const { return m_isStarted; }

    Q_INVOKABLE QString getDisplayText();

public slots:
    void startHW();
    void stopHW();
    void restartHW();

signals:
    void message(const QString& msg);
    void displayUpdated();

// QThread interface
protected:
    virtual void run() override;

private:
    void initOptable();
    void initDiskFromFile();
    void createTestDiskFile();
    void boot();
    void run2();
    void getCurrentCommand();
    void execCurrentCommand();

private:
    void opfunc0();
    void opfunc1();
    void opfunc2();

private:
    static QString arrayToString(const char* array, int length);

private:
    // state
    bool m_isStarted;

    // registers
    quint32 m_PC;
    unsigned char* m_executedCommand;

    // memory
    unsigned char* m_memory;
    unsigned char* m_disk;

    // optable
    QHash<int, opfunc>* m_optable;

    // display memory (video memory) (text mode)
    unsigned char* m_display;

    HardwareThread* m_hardwareThread;
};

#endif // HARDWARE_H
