#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "checkersmodel.h"
#include "gamesettingsmanager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    CheckersModel checkersModelInstance;
    GameSettingsManager gameSettingsManager;

    checkersModelInstance.resetModel();

    qRegisterMetaType<CornersCoordinates>("CheckersModel::CornersCoordinates");
    qRegisterMetaType<Piece>("Piece");

    qRegisterMetaType<CheckersModel::Player>("CheckersModel::Player");
    qRegisterMetaType<CheckersModel::Type>("CheckersModel::Type");

    qRegisterMetaType<GameSettingsManager::GameMode>("GameSettingsManager::GameMode");
    qRegisterMetaType<GameSettingsManager::GameTime>("GameSettingsManager::GameTime");

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("checkersModelInstance", &checkersModelInstance);    
    engine.rootContext()->setContextProperty("gameSettingsManager", &gameSettingsManager);

    qmlRegisterUncreatableMetaObject(CheckersModel::staticMetaObject,
                                     "CheckersEnums", 1, 0,
                                     "CheckersModel",
                                     "Error: Only enums");

    qmlRegisterType<CheckersModel>("checkers.model", 1, 0, "CheckersModel");
    qmlRegisterType<GameSettingsManager>("game.settings", 1, 0, "GameSettingsManager");

    qmlRegisterUncreatableType<CornersCoordinates>("Checkers", 1, 0, "cornersCoordinates", "CornersCoordinates cannot be created in QML");
    qmlRegisterUncreatableType<Piece>("Checkers", 1, 0, "piece", "Piece cannot be created in QML");

    qmlRegisterUncreatableType<GameSettingsManager>("GameSettingsManager", 1, 0, "GameMode", "Only enums exposed");

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
