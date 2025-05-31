#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H

#include <QObject>
#include "checkersmodel.h"

class ComputerPlayer : public QObject
{
    Q_OBJECT
public:
    explicit ComputerPlayer(QObject *parent = nullptr);
    explicit ComputerPlayer(CheckersModel *model, CheckersModel::Player playerColor);

    void makeMove();
signals:

private:
    CheckersModel* m_model;
    CheckersModel::Player m_playerColor;

    QModelIndexList getAllValidMoves();
};

#endif // COMPUTERPLAYER_H
