#include "computerplayer.h"
//***************************************************************************************************************************************************************************************************************************************
ComputerPlayer::ComputerPlayer(QObject *parent)
    : QObject{parent}
{}
//***************************************************************************************************************************************************************************************************************************************
ComputerPlayer::ComputerPlayer(CheckersModel *model, CheckersModel::Player playerColor)
    : m_model(model), m_playerColor(playerColor)
{
    Q_ASSERT(m_model);
}
//***************************************************************************************************************************************************************************************************************************************
void ComputerPlayer::makeMove()
{
    //getAllMovablePieces();
    QPair<QModelIndex, QPair<char, int> > randomMove = getRandomMove();
    qDebug() << "random move got: " << randomMove;
}
//***************************************************************************************************************************************************************************************************************************************
QModelIndexList ComputerPlayer::getAllMovablePieces()
{
    QModelIndexList movablePieces = {};

    for(int row = 0; row < m_model->getRowsNo(); row++) {
        for(int column = 0; column < m_model->getColumnsNo(); column++) {
            QModelIndex idx = m_model->index(row, column);
            QVariant range = m_model->data(idx, CheckersModel::RangeRole);
            //qDebug() << "index: " << "range: " << range;
            //qDebug() << "range type name:" << range.typeName();
            if (range.canConvert<QVariantList>()) {
                QVariantList list = range.toList();
                if (!list.isEmpty() && !m_model->getPieceColor(idx)) {
                    movablePieces.append(idx);
                    //qDebug() << "Movable piece at:" << idx << "range:" << list;
                }
            }

        }
    }
    return movablePieces;
}
//***************************************************************************************************************************************************************************************************************************************
QPair<QModelIndex, QPair<char, int> > ComputerPlayer::getRandomMove()
{
    QModelIndexList movablePieces = getAllMovablePieces();
    if (movablePieces.isEmpty()) {
        return {};
    }

    int pieceIdx = QRandomGenerator::global()->bounded(movablePieces.size());
    QModelIndex selectedPiece = movablePieces.at(pieceIdx);
    qDebug() << "drawn piece: " << selectedPiece;

    QVariant rangeVar = m_model->data(selectedPiece, CheckersModel::RangeRole);
    QVariantList rangeList = rangeVar.toList();

    if (rangeList.isEmpty()) {
        return {}; // it shouldn't happen
    }

    int moveIdx = QRandomGenerator::global()->bounded(rangeList.size());
    QPair<char, int> move = qvariant_cast<QPair<char, int>>(rangeList.at(moveIdx));
    qDebug() << "drawn move, piece: " << selectedPiece << ", move: " << move;

    return { selectedPiece, move };
}
//***************************************************************************************************************************************************************************************************************************************
