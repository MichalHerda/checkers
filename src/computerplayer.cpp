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
ComputerPlayer::ComputerPlayer(CheckersModel *model,
                               CheckersModel::Player playerColor,
                               GameController *controller,
                               GameLogic *logic,
                               QObject *parent)
    : QObject(parent),
    m_model(model),
    m_playerColor(playerColor),
    m_gameController(controller),
    m_logic(logic)
{}
//***************************************************************************************************************************************************************************************************************************************
void ComputerPlayer::makeMove()
{
    QPair<QModelIndex, QPair<char, int> > randomMove = getRandomMove();
    qDebug() << "random move got: " << randomMove;

    QPair<char, int> targetPair = randomMove.second;
    char targetColumn = randomMove.second.first;
    int targetRow = randomMove.second.second;
    qDebug() << "target pair: " << targetPair;
    qDebug() << "target column: " << targetColumn << ", target row: " << targetRow;
    QModelIndex indexTarget = m_model->indexFromPair(targetPair);
    qDebug() << "index from pair (target)" << indexTarget;
    QModelIndex indexToMove = randomMove.first;
    qDebug() << "index to move: " << indexToMove;

    m_gameController->setModelIndexToMove(indexToMove);

    QVariant emptyPieceData = m_model->data(indexToMove, CheckersModel::PieceRole);

    QVariant pieceData = m_model->data(indexTarget, CheckersModel::PieceRole);

    m_model->setData(indexToMove, pieceData, CheckersModel::PieceRole);
    m_model->setData(indexTarget, emptyPieceData, CheckersModel::PieceRole);

    m_gameController->setAllPiecesRange();
}
//***************************************************************************************************************************************************************************************************************************************
void ComputerPlayer::makeCapture()
{
    QModelIndexList capturePieces = getAllCapturePieces();
    if (capturePieces.isEmpty()) {
        qDebug() << "capturePieces empty";
        return;
    }
    qDebug() << "capture pieces: " << capturePieces;

    int randomIndex = QRandomGenerator::global()->bounded(capturePieces.size());
    QModelIndex indexToMove = capturePieces[randomIndex];
    qDebug() << "index to move: " << indexToMove;

    QVariant rangeData = m_model->data(indexToMove, CheckersModel::RangeRole);
    QVariantList rangeList = rangeData.toList();

    if(rangeList.isEmpty()) return;

    int randomMoveIndex = QRandomGenerator::global()->bounded(rangeList.size());
    QPair<char, int> targetPair = rangeList[randomMoveIndex].value<QPair<char, int>>();
    QModelIndex indexTarget = m_model->indexFromPair(targetPair);
    qDebug() << "index target: "  << indexTarget;

    //
    m_gameController->setModelIndexToMove(indexToMove);

    QVariant emptyPieceData = m_model->data(indexToMove, CheckersModel::PieceRole);

    QVariant pieceData = m_model->data(indexTarget, CheckersModel::PieceRole);

    m_model->setData(indexToMove, pieceData, CheckersModel::PieceRole);
    m_model->setData(indexTarget, emptyPieceData, CheckersModel::PieceRole);

    m_gameController->setAllPiecesRange();
    m_logic->removePiece(indexToMove, indexTarget);

}
//***************************************************************************************************************************************************************************************************************************************
CheckersModel::Player ComputerPlayer::getComputerPlayer()
{
    return m_playerColor;
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
QModelIndexList ComputerPlayer::getAllCapturePieces()
{
    QModelIndexList capturePieces = {};

    for(int row = 0; row < m_model->getRowsNo(); row++) {
        for(int column = 0; column < m_model->getColumnsNo(); column++) {
            QModelIndex idx = m_model->index(row, column);
            QVariant isCaptureAvailable = m_model->data(idx, CheckersModel::CaptureAvailableRole);
            qDebug() << "isCaptureAvailableRole, index: " << idx << ": " << isCaptureAvailable;
            //if(isCaptureAvailable.canConvert<QVariantList>()) {
                if(isCaptureAvailable.toBool() == true) {
                    capturePieces.append(idx);
                }
            //}
        }
    }


    return capturePieces;
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
