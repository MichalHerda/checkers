#ifndef GAME_H
#define GAME_H

#include <QObject>
#include "checkersmodel.h"

class Game : public QObject
{
    Q_OBJECT

    Q_PROPERTY (bool gameOn                    READ gameOnRead     WRITE gameOnWrite     NOTIFY gameOnChanged     )
    Q_PROPERTY (CheckersModel::Player player   READ playerRead     WRITE playerWrite     NOTIFY playerChanged     )

public:
    explicit Game(QObject *parent = nullptr);

    bool gameOn = false;
    CheckersModel::Player player = CheckersModel::Player::null;

    bool gameOnRead()const;
    CheckersModel::Player playerRead()const;

    void gameOnWrite(bool gameOn);
    void playerWrite(CheckersModel::Player _player);

signals:
    void gameOnChanged(bool _gameOn);
    void playerChanged(CheckersModel::Player _player);

};

#endif // GAME_H
