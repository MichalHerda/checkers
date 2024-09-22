#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "checkersmodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    qmlRegisterType<CheckersModel>("checkers.model", 1, 0, "CheckersModel");
    const QUrl url(QStringLiteral("qrc:/Checkers/gui/Main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
