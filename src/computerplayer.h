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

    Q_INVOKABLE void makeMove();
signals:

private:
    CheckersModel* m_model;
    CheckersModel::Player m_playerColor;

    QModelIndexList getAllMovablePieces();
};

#endif // COMPUTERPLAYER_H
