#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <QObject>
#include "checkersmodel.h"

/*
    mustCapture(Player player)

    isCaptureAvailable(const QModelIndex &index)

    getManMoves(...)

    getKingMoves(...)

    isOpponentAt(...)

    getPlayerForCheck(...)

    canKingContinueCaptureFrom(...)

    reduceToBestKingCaptures(...)
*/

class GameLogic : public QObject
{
    Q_OBJECT
public:
    //explicit GameLogic(QObject *parent = nullptr);
    explicit GameLogic(CheckersModel* model, int rows, int columns);

    bool mustCapture(CheckersModel::Player player);
    bool isCaptureAvailable(const QModelIndex &index);
    bool isOpponentAt(const QModelIndex &index, CheckersModel::Player playerForCheck);

signals:

private:
    int m_rows;
    int m_columns;

    CheckersModel* m_model;
};

#endif // GAMELOGIC_H
