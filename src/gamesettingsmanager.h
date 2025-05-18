#ifndef GAMESETTINGSMANAGER_H
#define GAMESETTINGSMANAGER_H

#include <QObject>
#include <QMetaEnum>

class GameSettingsManager : public QObject
{
    Q_OBJECT

public:
    enum class GameMode {
        humanVsComputer,
        humanVsHumanHotSeat,
        humanVsHumanOnline
    };
    Q_ENUM(GameMode)

    enum class GameTime {
        minute1,
        minutes2,
        minutes5,
        minutes10,
        minutes15,
        minutes20,
        minutes30,
        nolimit
    };
    Q_ENUM(GameTime)

    explicit GameSettingsManager(QObject *parent = nullptr);

    Q_PROPERTY(GameMode gameMode READ gameModeRead WRITE gameModeWrite NOTIFY gameModeChanged)
    Q_PROPERTY(GameTime gameTime READ gameTimeRead WRITE gameTimeWrite NOTIFY gameTimeChanged)

    GameSettingsManager::GameMode gameModeRead()const;
    GameSettingsManager::GameTime gameTimeRead()const;

    void gameModeWrite(GameSettingsManager::GameMode _gameMode);
    void gameTimeWrite(GameSettingsManager::GameTime _gameTime);

    void loadSettings();
    void saveSettings();

signals:
    void gameModeChanged(GameSettingsManager::GameMode _gameMode);
    void gameTimeChanged(GameSettingsManager::GameTime _gameTime);

private:
    GameMode m_gameMode = GameSettingsManager::GameMode::humanVsHumanHotSeat;
    GameTime m_gameTime = GameSettingsManager::GameTime::minutes5;

};

#endif // GAMESETTINGSMANAGER_H
