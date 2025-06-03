#include "gamelogic.h"
//***************************************************************************************************************************************************************************************************************************************
//GameLogic::GameLogic(QObject *parent)
//    : QObject{parent}
//{}
//***************************************************************************************************************************************************************************************************************************************
GameLogic::GameLogic(CheckersModel* model, int rows, int columns)
    : m_model(model), m_rows(rows), m_columns(columns)
{

}
//***************************************************************************************************************************************************************************************************************************************
bool GameLogic::mustCapture(CheckersModel::Player player)
{
    for(int row = 0, arrayIdx = 0; row < m_rows; row++) {
        for(int column = 0; column < m_columns; column++) {
            QModelIndex index = m_model->getIndex(row, column);
            bool isWhite =  m_model->getPieceColor(index);
            bool isCurrentPlayer = (player == CheckersModel::Player::white && isWhite) || (player == CheckersModel::Player::black && !isWhite);
            if(isCurrentPlayer) {
                bool captureAvailable =  /*m_model->*/isCaptureAvailable(index);
                if(captureAvailable) {
                    return true;
                }
            }
        }
    }
    return false;
}
//***************************************************************************************************************************************************************************************************************************************
bool GameLogic::isCaptureAvailable(const QModelIndex &index)
{
    qDebug() << "gameLogic isCaptureAvailable";
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
                QModelIndex nextIdx = m_model->getIndex(r, c);
                if (m_model->isPiecePresent(nextIdx) && !foundOpponent) {
                    if (isOpponentAt(nextIdx, playerForCheck)) {
                        //qDebug() << "opponent found at: " << nextIdx;
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
                        QModelIndex checkIdx = m_model->getIndex(checkR, checkC);
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
                QModelIndex midIdx = m_model->getIndex(midR, midC);
                QModelIndex landIdx = m_model->getIndex(landR, landC);

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
bool GameLogic::isOpponentAt(const QModelIndex &index, CheckersModel::Player playerForCheck)
{
    return ( (playerForCheck == CheckersModel::Player::white)  &&  (!m_model->getPieceColor(index)) ) ||
           ( (playerForCheck == CheckersModel::Player::black)  &&  ( m_model->getPieceColor(index)) );
}
//***************************************************************************************************************************************************************************************************************************************
