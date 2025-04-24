#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "checkersmodel.h"
#include "game.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    CheckersModel checkersModelInstance;
    checkersModelInstance.resetModel();

    Game game;

    qRegisterMetaType<CornersCoordinates>("CheckersModel::CornersCoordinates");
    qRegisterMetaType<Piece>("Piece");

    qRegisterMetaType<CheckersModel::Player>("CheckersModel::Player");
    qRegisterMetaType<CheckersModel::Type>("CheckersModel::Type");

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("checkersModelInstance", &checkersModelInstance);
    engine.rootContext()->setContextProperty("game", &game);

    qmlRegisterUncreatableMetaObject(CheckersModel::staticMetaObject,
                                     "CheckersEnums", 1, 0,
                                     "CheckersModel",
                                     "Error: Only enums");

    qmlRegisterType<CheckersModel>("checkers.model", 1, 0, "CheckersModel");

    qmlRegisterUncreatableType<CornersCoordinates>("Checkers", 1, 0, "cornersCoordinates", "CornersCoordinates cannot be created in QML");
    qmlRegisterUncreatableType<Piece>("Checkers", 1, 0, "piece", "Piece cannot be created in QML");

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
