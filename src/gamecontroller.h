#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include <memory>
#include "checkersmodel.h"
#include "gamelogic.h"

class GameController : public QObject
{
    Q_OBJECT
public:
    explicit GameController(CheckersModel* model, QObject *parent = nullptr);
    explicit GameController(QObject *parent = nullptr);

    Q_PROPERTY (bool gameOn                    READ gameOnRead     WRITE gameOnWrite     NOTIFY gameOnChanged     )
    Q_PROPERTY (CheckersModel::Player player   READ playerRead     WRITE playerWrite     NOTIFY playerChanged     )
    Q_PROPERTY (CheckersModel::Player winner   READ winnerRead     WRITE winnerWrite     NOTIFY winnerChanged     )

    bool gameOn = false;
    CheckersModel::Player player = CheckersModel::Player::null;
    CheckersModel::Player winner = CheckersModel::Player::null;

    bool gameOnRead()const;
    CheckersModel::Player playerRead()const;
    CheckersModel::Player winnerRead()const;

    void gameOnWrite(bool gameOn);
    void playerWrite(CheckersModel::Player _player);
    void winnerWrite(CheckersModel::Player _winner);

    Q_INVOKABLE bool isPlayersOwnPiece(const QModelIndex idx);
    Q_INVOKABLE bool isMoveValid(QModelIndex index, double averageX, double averageY);
    Q_INVOKABLE void executeMove(QModelIndex index, double averageX, double averageY);
    Q_INVOKABLE void evaluatePromotionToKing(QModelIndex index, double averageX, double averageY);
    Q_INVOKABLE bool isCaptureAvailable(const QModelIndex &index);
    Q_INVOKABLE void changePlayer(double averageX, double averageY, bool mustCapture);
    Q_INVOKABLE bool mustCapture(CheckersModel::Player player);
    Q_INVOKABLE void updateAllPiecesRange();
    Q_INVOKABLE void resetModel();
    Q_INVOKABLE void setAllPiecesRange();
    Q_INVOKABLE void showScore();
    Q_INVOKABLE void checkForWinner();
    Q_INVOKABLE bool isGameOver();

    void setModelIndexToMove(QModelIndex idx);
    QModelIndex getModelIndexToMove();

signals:
    void gameOnChanged(bool _gameOn);
    void playerChanged(CheckersModel::Player _player);
    void winnerChanged(CheckersModel::Player _winner);

private:
    CheckersModel* m_model;
    std::unique_ptr<GameLogic> m_logic;
    QModelIndex m_modelIndexToMove;
    bool m_hasMultiCapture = false;

    bool isPlayerBlocked(CheckersModel::Player player);
};

#endif // GAMECONTROLLER_H
