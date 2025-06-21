#include "computerplayer.h"

ComputerPlayer::ComputerPlayer(QObject *parent)
    : QObject{parent}
{}
/*
ComputerPlayer::ComputerPlayer(CheckersModel *model, CheckersModel::Player playerColor)
{

}
*/
ComputerPlayer::ComputerPlayer(CheckersModel *model, CheckersModel::Player playerColor)
    : m_model(model), m_playerColor(playerColor)
{
    Q_ASSERT(m_model); // zabezpieczenie — wywali się tu, jeśli model był nullptr
}

void ComputerPlayer::makeMove()
{
    getAllMovablePieces();
}

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
                    qDebug() << "Movable piece at:" << idx << "range:" << list;
                }
            }

        }
    }
    return movablePieces;
}
