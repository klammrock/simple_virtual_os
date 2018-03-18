#include "hardware.h"

#include <QDebug>
#include <QFile>

static const quint32 MEMORY_SIZE_BYTES = 256;
static const quint32 DISK_SIZE_BYTES = 1024;
static const quint32 COMMAND_SIZE_BYTES = 1;

static const quint32 DISK_BOOT_LOADER_SIZE_BYTES = 256;

static const QString DISK_FILENAME = "test_disk.bin";

Hardware::Hardware(QObject* parent) :
    QObject(parent),
    m_isStarted(false),
    m_PC(0),
    m_executedCommand(new unsigned char[COMMAND_SIZE_BYTES]),
    m_memory(new unsigned char[MEMORY_SIZE_BYTES]),
    m_disk(new unsigned char[DISK_SIZE_BYTES])
{
    qDebug() << "Hardware()";

    // clear memory and registers
    std::fill(m_executedCommand, m_executedCommand + COMMAND_SIZE_BYTES, 0);
    std::fill(m_memory, m_memory + MEMORY_SIZE_BYTES, 0);
    std::fill(m_disk, m_disk + DISK_SIZE_BYTES, 0);

    // init disk from binary file
    initDiskFromFile();
}

Hardware::~Hardware()
{
    qDebug() << "~Hardware()";
    delete m_memory;
    delete m_disk;
}

//void Hardware::startI()
//{
//    qDebug() << "startI";
//    emit message("startI");
//}

void Hardware::start()
{
    m_isStarted = true;
    qDebug() << "start";
    emit message("start");

    boot();
    run();
}

void Hardware::stop()
{
    m_isStarted = false;
    qDebug() << "stop";
    emit message("stop");
}

void Hardware::restart()
{
    stop();
    start();
}

void Hardware::initDiskFromFile()
{
    if (!QFile::exists(DISK_FILENAME))
        createTestDiskFile();

    QFile diskFile(DISK_FILENAME);
    diskFile.open(QIODevice::ReadOnly);
    qint64 len = diskFile.read((char *)m_disk, DISK_SIZE_BYTES);
    qDebug() << "Read disk from file bytes:" << len;
    diskFile.close();
}

void Hardware::createTestDiskFile()
{
    QFile diskFile(DISK_FILENAME);
    diskFile.open(QIODevice::WriteOnly);
    QByteArray array;
    array.append(1);
    diskFile.write(array);
    qDebug() << "Write disk to file";
    diskFile.close();
}

void Hardware::boot()
{
    qDebug() << "booting";
    memcpy(m_memory, m_disk, DISK_BOOT_LOADER_SIZE_BYTES);
}

void Hardware::run()
{
    qDebug() << "running";
    getCurrentCommand();
    execCurrentCommand();
}

void Hardware::getCurrentCommand()
{
    memcpy(m_executedCommand, m_memory, COMMAND_SIZE_BYTES);
    m_PC += COMMAND_SIZE_BYTES;
}

void Hardware::execCurrentCommand()
{
    unsigned char byte1 = m_executedCommand[0];

    switch (byte1) {
    case 0:
        qDebug() << "0";
        break;
    case 1:
        qDebug() << "1";
        emit message("exec command 1");
        break;
    default:
        qDebug() << "default";
        break;
    }
}
