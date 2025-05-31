#include "computerplayer.h"

ComputerPlayer::ComputerPlayer(QObject *parent)
    : QObject{parent}
{}

ComputerPlayer::ComputerPlayer(CheckersModel *model, CheckersModel::Player playerColor)
{

}

void ComputerPlayer::makeMove()
{

}

QModelIndexList ComputerPlayer::getAllValidMoves()
{
    QModelIndexList validMovesList = {};
    return validMovesList;
}
