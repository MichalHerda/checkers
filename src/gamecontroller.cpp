#include "gamecontroller.h"
//***************************************************************************************************************************************************************************************************************************************
GameController::GameController(CheckersModel* model, QObject *parent)
    : QObject{parent}, m_model(model)
{
    m_logic = std::make_unique<GameLogic>(model, model->getRowsNo(), model->getColumnsNo());
}
//***************************************************************************************************************************************************************************************************************************************
GameController::GameController(QObject *parent)
{

}
//***************************************************************************************************************************************************************************************************************************************
bool GameController::gameOnRead()const {
    return gameOn;
}
//***************************************************************************************************************************************************************************************************************************************
CheckersModel::Player GameController::playerRead()const {
    return player;
}
//***************************************************************************************************************************************************************************************************************************************
void GameController::gameOnWrite(bool _gameOn) {
    gameOn = _gameOn;
    emit gameOnChanged(_gameOn);
}
//***************************************************************************************************************************************************************************************************************************************
void GameController::playerWrite(CheckersModel::Player _player) {
    player = _player;
    emit playerChanged(_player);
}
//***************************************************************************************************************************************************************************************************************************************
bool GameController::isPlayersOwnPiece(const QModelIndex idx)
{
    return m_model->CheckersModel::getPieceColor(idx) && player == CheckersModel::Player::white ||
          !m_model->CheckersModel::getPieceColor(idx) && player == CheckersModel::Player::black;
}
//***************************************************************************************************************************************************************************************************************************************
bool GameController::isMoveValid(QModelIndex index, double averageX, double averageY)
{
    qDebug() << "isMoveValid, index passed: " << index;
    QVariantList range = m_model -> data(index, CheckersModel::RangeRole).toList();
    qDebug() << "passed index range: "  << range;

    auto hasCapture = m_model -> data(index, CheckersModel::CaptureAvailableRole);
    if(!hasCapture.toBool() && mustCapture(player)) {
        return false;
    }

    QPointF pieceCenter(averageX, averageY);
    QModelIndex targetFieldIndex = m_model->findFieldIndexForPieceCenter(pieceCenter);
    qDebug() << "piece center is now inside field: " << targetFieldIndex;

    std::pair<char, int> targetCoordinate = m_model->data(targetFieldIndex, CheckersModel::FieldNameRole).value<std::pair<char, int>>();
    qDebug() << "target coordinate: " << targetCoordinate;
    for (const QVariant &item : range) {
        std::pair<char, int> rangeCoordinate = item.value<std::pair<char, int>>();
        if (rangeCoordinate == targetCoordinate) {
            qDebug() << "Pole docelowe znajduje się w zakresie ruchu pionka.";
            return true;
        }
    }

    qDebug() << "Pole docelowe nie znajduje się w zakresie pionka";
    return false;
}
//***************************************************************************************************************************************************************************************************************************************
void GameController::executeMove(QModelIndex index, double averageX, double averageY)
{
    setModelIndexToMove(m_model->getModelIndexFromGivenCoordinates(averageX, averageY));
    QModelIndex indexToMove = getModelIndexToMove();

    QVariant emptyPieceData = m_model->data(indexToMove, CheckersModel::PieceRole);

    QVariant pieceData = m_model->data(index, CheckersModel::PieceRole);

    bool isCapture = mustCapture(player);

    if(isCapture) {
        m_logic->removePiece(index, indexToMove);
    }

    m_model->setData(indexToMove, pieceData, CheckersModel::PieceRole);
    m_model->setData(index, emptyPieceData, CheckersModel::PieceRole);

    setAllPiecesRange();
}
//***************************************************************************************************************************************************************************************************************************************
void GameController::evaluatePromotionToKing(QModelIndex index,double averageX, double averageY)
{
    qDebug() << "evaluate promotion to king, averageX: " << averageX << "averageY: " << averageY << "index: " << index;
    QModelIndex modelIndexToMove = m_model->getModelIndexFromGivenCoordinates(averageX, averageY);
    qDebug() << "modelIndexToMove: " << modelIndexToMove;
    bool hasMultiCapture = isCaptureAvailable(m_modelIndexToMove);
    qDebug() << "hasMultiCapture: " << hasMultiCapture;
    qDebug() << "_hasMultiCapture: " << m_hasMultiCapture;
    qDebug() << "player: " << player;
    qDebug() << "getPieceType: " << m_model->getPieceType(index);
    qDebug() << "row: " << modelIndexToMove.row();

    if(!m_hasMultiCapture) {
        if(player == CheckersModel::Player::white &&
            m_model->getPieceType(index) == false &&
            modelIndexToMove.row() == 0) {
            qDebug() << "promote to king";
            m_model->setEmptyField(modelIndexToMove);
            m_model->setPiece(modelIndexToMove, player, CheckersModel::Type::king);
        }

        if(player == CheckersModel::Player::black &&
            m_model->getPieceType(index) == false &&
            modelIndexToMove.row() == 7) {
            qDebug() << "promote to king";
            m_model->setEmptyField(modelIndexToMove);
            m_model->setPiece(modelIndexToMove, player, CheckersModel::Type::king);
        }
    }
}
//***************************************************************************************************************************************************************************************************************************************
void GameController::changePlayer(double averageX, double averageY, bool mustCapture)
{
    qDebug() << "CHANGE PLAYER: ";
    qDebug() << "   player: " << player;
    QModelIndex indexToMove = m_model->getModelIndexFromGivenCoordinates(averageX, averageY);
    qDebug() << "   indexToMove: " << indexToMove;
    qDebug() << "   isCapture: " << mustCapture;
    bool hasMultiCapture = isCaptureAvailable(indexToMove);
    qDebug() << "   hasMultiCapture: " << hasMultiCapture;

    if(!hasMultiCapture || !mustCapture) {
        if(player == CheckersModel::Player::white) {
            player = CheckersModel::Player::black;
            emit playerChanged(CheckersModel::Player::black);
        }
        else {
            player = CheckersModel::Player::white;
            emit playerChanged(CheckersModel::Player::white);
        }
    }
}
//***************************************************************************************************************************************************************************************************************************************
bool GameController::mustCapture(CheckersModel::Player player)
{
    if(m_logic) {
        return m_logic -> mustCapture(player);
    }
    else {
        qDebug() << "m_logic is nullptr!";
        return false;
    }
}
//***************************************************************************************************************************************************************************************************************************************
void GameController::updateAllPiecesRange()
{
    m_logic->setAllPiecesRange();
}
//***************************************************************************************************************************************************************************************************************************************
void GameController::resetModel()
{
    m_logic->resetModel();
}
//***************************************************************************************************************************************************************************************************************************************
void GameController::setAllPiecesRange()
{
    m_logic->setAllPiecesRange();
}
//***************************************************************************************************************************************************************************************************************************************
void GameController::showScore()
{
    m_logic->showScore();
}
//***************************************************************************************************************************************************************************************************************************************
void GameController::setModelIndexToMove(QModelIndex idx)
{
    m_modelIndexToMove = idx;
}
//***************************************************************************************************************************************************************************************************************************************
QModelIndex GameController::getModelIndexToMove()
{
    return m_modelIndexToMove;
}
//***************************************************************************************************************************************************************************************************************************************
bool GameController::isCaptureAvailable(const QModelIndex &index)
{
    if (!m_model->isPiecePresent(index)) {
        //qDebug() << "isCaptureAvailable function. Piece not present";
        return false;
    }

    bool isWhite = m_model->getPieceColor(index);
    bool isKing = m_model->getPieceType(index);

    CheckersModel::Player playerForCheck = m_model->getPlayerForCheck(index);

    int row = index.row();
    int col = index.column();

    const int dr[] = {-1, -1, 1, 1}; // góra-lewo, góra-prawo, dół-lewo, dół-prawo
    const int dc[] = {-1, 1, -1, 1};

    if (isKing) {
        //qDebug() << "isCaptureAvailable Role KING, index: " << index << "player for check: " << playerForCheck;
        for (int dir = 0; dir < 4; ++dir) {
            int r = row + dr[dir];
            int c = col + dc[dir];
            bool foundOpponent = false;
            QModelIndex opponentIdx = QModelIndex();
            while (m_model->isInsideBoard(r, c)) {
                //qDebug() << "r: " << r;
                //qDebug() << "c: " << c;
                QModelIndex nextIdx = m_model->index(r, c);
                if (m_model->isPiecePresent(nextIdx) && !foundOpponent) {
                    if (m_logic->isOpponentAt(nextIdx, playerForCheck)) {
                        qDebug() << "opponent found at: " << nextIdx;
                        opponentIdx = nextIdx;
                        foundOpponent = true;
                    }
                    else {
                        //qDebug() << "your soldier found at: " << nextIdx;
                        break;
                    }
                    //else break;
                }
                else {
                    if (foundOpponent) {
                        int checkR = opponentIdx.row() + dr[dir];
                        int checkC = opponentIdx.column() + dc[dir];
                        QModelIndex checkIdx = m_model->index(checkR, checkC);
                        //qDebug() << "nextIdx: " << checkIdx << "row: " << r << "column: " << c;
                        if (m_model->isInsideBoard(r, c) &&
                            !m_model->isPiecePresent(nextIdx) ) {
                            //qDebug() << "empty field found: " << nextIdx << ", capture available for king";
                            return true;
                        }
                        else if ( (m_model->isInsideBoard(r,c)) &&
                                 m_model->isPiecePresent(nextIdx) ) {
                            //qDebug() << "piece present, cannot move " << nextIdx;
                            break;
                        }
                        else {
                            //qDebug() << "neither empty field found nor piece present";
                            break;
                        }
                    }
                }
                //qDebug() << "continue searching for next field...";
                r += dr[dir];
                c += dc[dir];
            }
        }
    }
    else {
        //qDebug() << "isCaptureAvailable Role MAN";
        for (int dir = 0; dir < 4; ++dir) {
            int midR = row + dr[dir];
            int midC = col + dc[dir];
            int landR = row + 2 * dr[dir];
            int landC = col + 2 * dc[dir];

            if (m_model->isInsideBoard(landR, landC)) {
                QModelIndex midIdx = m_model->index(midR, midC);
                QModelIndex landIdx = m_model->index(landR, landC);

                if (m_model->isPiecePresent(midIdx) &&
                    m_model->getPieceColor(midIdx) != isWhite &&
                    !m_model->isPiecePresent(landIdx)) {
                    return true;
                }
            }
        }
    }
    return false;
}
//***************************************************************************************************************************************************************************************************************************************
