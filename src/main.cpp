#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "checkersmodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    CheckersModel checkersModelInstance;
    checkersModelInstance.resetModel();

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("checkersModelInstance", &checkersModelInstance);

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
