#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <QObject>
#include "checkersmodel.h"

class GameLogic : public QObject
{
    Q_OBJECT
public:
    //explicit GameLogic(QObject *parent = nullptr);
    explicit GameLogic(CheckersModel* model, int rows, int columns);

    bool mustCapture(CheckersModel::Player player);
    bool isCaptureAvailable(const QModelIndex &index);
    bool isOpponentAt(const QModelIndex &index, CheckersModel::Player playerForCheck);
    void setAllPiecesRange();
    void removePiece(QModelIndex from, QModelIndex to);
    void resetModel();
    void initializePieces();
    void deselectAllFields();
    void showScore();
    int getWhiteScore();
    int getBlackScore();

signals:

private:
    int m_rows;
    int m_columns;

    CheckersModel* m_model;

    QList <QPair <char, int> > getKingMoves(const QModelIndex &index, bool isWhite);
    QList <QPair <char, int> > getManMoves(const QModelIndex &index, bool isWhite);
    void reduceToBestKingCaptures(const QModelIndex &initialIdx, QList<QPair<char, int>> &captureMoves);
    bool canKingContinueCaptureFrom(int row, int col, QModelIndex initialKingIdx, QList<QModelIndex> &pathMoves, QList<QModelIndex> &checkedMoves);
};

#endif // GAMELOGIC_H
