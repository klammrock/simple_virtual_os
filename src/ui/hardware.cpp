#include "hardware.h"

#include <QDebug>
#include <QFile>

#include "hardwarethread.h"

static const quint32 MEMORY_SIZE_BYTES = 256;
static const quint32 DISK_SIZE_BYTES = 1024;
static const quint32 COMMAND_SIZE_BYTES = 4;
/*
 * | opcode | operand |
 * 1b       3b
*/

static const quint32 DISK_BOOT_LOADER_SIZE_BYTES = 256;

static const QString DISK_FILENAME = "test_disk.bin";

static const bool FORCE_REWRITE_DISK_FILE = false;

Hardware::Hardware(QObject* parent) :
    QThread(parent),
    m_isStarted(false),
    m_PC(0),
    m_executedCommand(new unsigned char[COMMAND_SIZE_BYTES]),
    m_memory(new unsigned char[MEMORY_SIZE_BYTES]),
    m_disk(new unsigned char[DISK_SIZE_BYTES]),
    m_optable(new QHash<int, opfunc>()),
    m_hardwareThread(nullptr)
{
    qDebug() << "Hardware()";

    initOptable();

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
    delete m_optable;
}

void Hardware::run()
{
    qDebug() << "thread running";

    exec();
}


//void Hardware::startI()
//{
//    qDebug() << "startI";
//    emit message("startI");
//}

void Hardware::startHW()
{
    m_isStarted = true;
    qDebug() << "start";
    emit message("start");

    boot();
    run2();

    //start();
    if (m_hardwareThread == nullptr)
        m_hardwareThread = new HardwareThread();
    m_hardwareThread->start();
}

void Hardware::stopHW()
{
    m_isStarted = false;
    qDebug() << "stop";
    emit message("stop");

    if (m_hardwareThread != nullptr) {
        //m_hardwareThread->quit();
        m_hardwareThread->stopRequest();
    }
}

void Hardware::restartHW()
{
    stopHW();
    startHW();
}

void Hardware::initOptable()
{
    (*m_optable)[0] = &Hardware::opfunc1;
    (*m_optable)[1] = &Hardware::opfunc1;
    (*m_optable)[2] = &Hardware::opfunc1;
}

void Hardware::initDiskFromFile()
{
    if (FORCE_REWRITE_DISK_FILE || !QFile::exists(DISK_FILENAME))
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
    array.fill(0, COMMAND_SIZE_BYTES);
    array[0] = 1;
    array[3] = 2;
    diskFile.write(array);

    array.fill(0, COMMAND_SIZE_BYTES);
    array[0] = 1;
    array[3] = 3;
    diskFile.write(array);

    array.fill(0, COMMAND_SIZE_BYTES);
    diskFile.write(array);

    qDebug() << "Write disk to file";
    diskFile.close();
}

void Hardware::boot()
{
    qDebug() << "booting";
    memcpy(m_memory, m_disk, DISK_BOOT_LOADER_SIZE_BYTES);
}

void Hardware::run2()
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

    auto f = (*m_optable)[byte1];
    (this->*f)();
}

void Hardware::opfunc0()
{
    qDebug() << "opfunc0() -> stop hw";
}

void Hardware::opfunc1()
{
    qDebug() << "opfunc1() -> show message: " << arrayToString((const char*)&m_executedCommand[1], COMMAND_SIZE_BYTES - 1);
}

void Hardware::opfunc2()
{
    qDebug() << "opfunc2() -> jmp";
}

QString Hardware::arrayToString(const char *array, int length)
{
    QString res = "";

    for (int i = 0; i < length; ++i) {
        res += QString::number(array[i], 16) + " ";
    }

    return res;
}
