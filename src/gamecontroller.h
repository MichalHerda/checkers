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

    Q_INVOKABLE bool isPlayersOwnPiece(const QModelIndex idx);
    Q_INVOKABLE bool isMoveValid(QModelIndex index, double averageX, double averageY);
    Q_INVOKABLE void executeMove(QModelIndex index, double averageX, double averageY);
    Q_INVOKABLE void evaluatePromotionToKing(QModelIndex index, double averageX, double averageY);
    Q_INVOKABLE void changePlayer(double averageX, double averageY, bool mustCapture);
    Q_INVOKABLE bool mustCapture(CheckersModel::Player player);
    Q_INVOKABLE void updateAllPiecesRange();

signals:

private:
    CheckersModel* m_model;
    std::unique_ptr<GameLogic> m_logic;
    QModelIndex m_modelIndexToMove;
    bool m_hasMultiCapture = false;
};

#endif // GAMECONTROLLER_H
