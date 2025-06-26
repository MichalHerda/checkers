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
QModelIndex ComputerPlayer::indexMovedRead() const
{
    return indexMoved;
}
//***************************************************************************************************************************************************************************************************************************************
void ComputerPlayer::indexMovedWrite(QModelIndex _indexMoved)
{
    qDebug() << "indexMoved write: " << _indexMoved;
    indexMoved = _indexMoved;
    emit indexMovedChanged(_indexMoved);
}
//***************************************************************************************************************************************************************************************************************************************
void ComputerPlayer::makeMove()
{
    // Losowanie opóźnienia od 1000 do 3000 ms
    int delayMs = QRandomGenerator::global()->bounded(1000, 3001); // górna granica wyłączna
    qDebug() << "Computer move delayed by (ms): " << delayMs;

    // Nie blokuje GUI – wykona performMove po opóźnieniu
    QTimer::singleShot(delayMs, this, &ComputerPlayer::performMove);
}
//***************************************************************************************************************************************************************************************************************************************
void ComputerPlayer::performMove()
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
    //emit indexMovedChanged(indexToMove);
    indexMovedWrite(indexToMove);

    m_gameController->setModelIndexToMove(indexToMove);

    QVariant emptyPieceData = m_model->data(indexToMove, CheckersModel::PieceRole);

    QVariant pieceData = m_model->data(indexTarget, CheckersModel::PieceRole);

    m_model->setData(indexToMove, pieceData, CheckersModel::PieceRole);
    m_model->setData(indexTarget, emptyPieceData, CheckersModel::PieceRole);
    setMovedPieceNewIndex(indexTarget);

    emit moveCompleted();
    m_gameController->setAllPiecesRange();
    //emit moveCompleted();
}
//***************************************************************************************************************************************************************************************************************************************
void ComputerPlayer::makeCapture()
{
    // Losowanie opóźnienia od 1000 do 3000 ms
    int delayMs = QRandomGenerator::global()->bounded(1000, 3001); // górna granica wyłączna
    qDebug() << "Computer move delayed by (ms): " << delayMs;

    // Nie blokuje GUI – wykona performMove po opóźnieniu
    QTimer::singleShot(delayMs, this, &ComputerPlayer::performCapture);
}
//***************************************************************************************************************************************************************************************************************************************
void ComputerPlayer::performCapture()
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
    setMovedPieceNewIndex(indexTarget);

    m_gameController->setAllPiecesRange();
    m_logic->removePiece(indexToMove, indexTarget);
    emit captureCompleted();

}
//***************************************************************************************************************************************************************************************************************************************
CheckersModel::Player ComputerPlayer::getComputerPlayer()
{
    return m_playerColor;
}
//***************************************************************************************************************************************************************************************************************************************
QModelIndex ComputerPlayer::getMovedPieceNewIndex()
{
    return m_movedPieceNewIndex;
}
//***************************************************************************************************************************************************************************************************************************************
void ComputerPlayer::setMovedPieceNewIndex(QModelIndex movedPieceNewIndex)
{
    m_movedPieceNewIndex = movedPieceNewIndex;
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
                if(isCaptureAvailable.toBool() == true && isComputerPlayerColor(idx)) {
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
bool ComputerPlayer::isComputerPlayerColor(QModelIndex idx)
{
    bool isBlack = !m_model->getPieceColor(idx);
    bool isWhite = m_model->getPieceColor(idx);

    if(getComputerPlayer() == CheckersModel::Player::white) {
        return isWhite;
    }
    if(getComputerPlayer() == CheckersModel::Player::black) {
        return isBlack;
    }
    return false;
}
//***************************************************************************************************************************************************************************************************************************************
