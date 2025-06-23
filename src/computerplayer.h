#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H

#include <QObject>
#include <QRandomGenerator>
#include "checkersmodel.h"
#include "gamecontroller.h"

class ComputerPlayer : public QObject
{
    Q_OBJECT
public:
    explicit ComputerPlayer(QObject *parent = nullptr);
    explicit ComputerPlayer(CheckersModel *model, CheckersModel::Player playerColor);
    explicit ComputerPlayer(CheckersModel *model,
                            CheckersModel::Player playerColor,
                            GameController *controller,
                            GameLogic *logic,
                            QObject *parent = nullptr);

    Q_INVOKABLE void makeMove();
    Q_INVOKABLE void makeCapture();
    Q_INVOKABLE CheckersModel::Player getComputerPlayer();
signals:

private:
    CheckersModel* m_model;
    GameController* m_gameController;
    GameLogic* m_logic;
    CheckersModel::Player m_playerColor;

    QModelIndexList getAllMovablePieces();
    QModelIndexList getAllCapturePieces();
    QPair<QModelIndex, QPair<char, int>> getRandomMove();
};

#endif // COMPUTERPLAYER_H
