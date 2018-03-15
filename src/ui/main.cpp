#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QQmlContext>

#include "main_lib.h"
#include "hardware.h"

int main(int argc, char *argv[])
{
    Main_lib lib;
    qDebug() << lib.getTrue();

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    auto hardware = new Hardware();
    engine.rootContext()->setContextProperty("mainViweModel", hardware);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
