#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H

#include <QObject>
#include <QRandomGenerator>
#include <QTimer>
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

    Q_PROPERTY (QModelIndex indexMoved  READ indexMovedRead WRITE indexMovedWrite NOTIFY indexMovedChanged)

    QModelIndex indexMoved = QModelIndex();
    QModelIndex indexMovedRead()const;
    void indexMovedWrite(QModelIndex _indexMoved);

    Q_INVOKABLE void makeMove();
    Q_INVOKABLE void makeCapture();
    Q_INVOKABLE CheckersModel::Player getComputerPlayer();
    Q_INVOKABLE QModelIndex getMovedPieceNewIndex();

    bool completed = false;
signals:
    void moveCompleted();
    void captureCompleted();
    void indexMovedChanged(QModelIndex _indexMoved);

private:
    CheckersModel* m_model;
    GameController* m_gameController;
    GameLogic* m_logic;
    CheckersModel::Player m_playerColor;
    QModelIndex m_movedPieceNewIndex;

    void performMove();
    void performCapture();
    void setMovedPieceNewIndex(QModelIndex movedPieceNewIndex);
    QModelIndexList getAllMovablePieces();
    QModelIndexList getAllCapturePieces();
    QPair<QModelIndex, QPair<char, int>> getRandomMove();
    bool isComputerPlayerColor(QModelIndex idx);
};

#endif // COMPUTERPLAYER_H
