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
QList <QPair <char, int> > GameLogic::getManMoves(const QModelIndex &index, bool isWhite)
{
    QList <QPair <char, int> > possibleMoves {};
    auto isCaptureAvailable = m_model->data(index, CheckersModel::CaptureAvailableRole);

    int rowNo = index.row();
    int colNo = index.column();
    int direction = isWhite ? -1 : 1;
    int captureDirection = (isWhite ? -2 : 2);

    if (isCaptureAvailable == false) {
        // Normalny ruch do przodu
        QList<QPoint> moveOffsets = { {direction, -1}, {direction, 1} };

        for (const QPoint& offset : moveOffsets) {
            int newRow = rowNo + offset.x();
            int newCol = colNo + offset.y();
            if (m_model->isInsideBoard(newRow, newCol)) {
                QModelIndex checkIndex = m_model->getIndex(newRow, newCol);
                if (!m_model->isPiecePresent(checkIndex)) {
                    QVariant move = m_model->data(checkIndex, CheckersModel::FieldNameRole);
                    possibleMoves.push_back(move.value<QPair<char, int>>());
                }
            }
        }
    }
    else {
        // Bicie w 4 kierunkach
        QList<QPoint> captureOffsets = { {captureDirection, -2}, {captureDirection, 2},
                                        {-captureDirection, -2}, {-captureDirection, 2} };

        for (const QPoint& offset : captureOffsets) {
            int newRow = rowNo + offset.x();
            int newCol = colNo + offset.y();
            int middleRow = rowNo + offset.x() / 2;
            int middleCol = colNo + offset.y() / 2;

            if (m_model->isInsideBoard(newRow, newCol) && m_model->isInsideBoard(middleRow, middleCol)) {
                QModelIndex targetIndex = m_model->getIndex(newRow, newCol);
                QModelIndex middleIndex = m_model->getIndex(middleRow, middleCol);

                if (!m_model->isPiecePresent(targetIndex)) { // cel musi być pusty
                    if (m_model->isPiecePresent(middleIndex)) { // na środku musi być pionek
                        bool middleIsWhite = m_model->getPieceColor(middleIndex);
                        if (middleIsWhite != isWhite) { // i przeciwnika
                            QVariant move = m_model->data(targetIndex, CheckersModel::FieldNameRole);
                            possibleMoves.push_back(move.value<QPair<char, int>>());
                        }
                    }
                }
            }
        }
    }
    return possibleMoves;
}
//***************************************************************************************************************************************************************************************************************************************
QList <QPair <char, int> > GameLogic::getKingMoves(const QModelIndex &index, bool isWhite)
{
    //qDebug() << "getKingMoves function: ";
    QList <QPair <char, int> > possibleMoves {};
    QList <QPair <char, int> > captureMoves {};

    int rowNo = index.row();
    int colNo = index.column();
    bool captureAvailable = isCaptureAvailable(index);
    CheckersModel::Player playerForCheck = m_model->getPlayerForCheck(index);

    const int dr[] = {-1, -1, 1, 1}; // góra-lewo, góra-prawo, dół-lewo, dół-prawo
    const int dc[] = {-1, 1, -1, 1};

    for (int dir = 0; dir < 4; ++dir) {
        int r = rowNo + dr[dir];
        int c = colNo + dc[dir];
        bool foundOpponent = false;

        while (m_model->isInsideBoard(r, c)) {
            QModelIndex currentIndex = m_model->getIndex(r, c);

            if (!m_model->isPiecePresent(currentIndex)) {
                //qDebug() << "   piece not present at " << currentIndex;
                if (!foundOpponent) {
                    if(!captureAvailable) {
                        //qDebug() << "       opponent not found, capture not available, add: " << currentIndex;
                        QVariant move = m_model->data(currentIndex, CheckersModel::FieldNameRole);
                        possibleMoves.push_back(move.value <QPair <char, int> > ());
                    }
                    else {
                        //qDebug() << "       opponent not found, capture available, no moves to add";
                    }
                }
                else {
                    if(!captureAvailable) {
                        //qDebug() << "       opponent found at " << currentIndex << ", capture available, no moves to add";
                    }
                    else {
                        //qDebug() << "       opponent found, capture available, add: " << currentIndex;
                        QVariant move = m_model->data(currentIndex, CheckersModel::FieldNameRole);
                        QPair <char, int> movePair = move.value <QPair <char, int> > ();
                        captureMoves.push_back(movePair);
                    }
                }

                r += dr[dir];
                c += dc[dir];

            }
            else {
                //qDebug() << "   piece present at " << currentIndex;
                if (isOpponentAt(currentIndex, playerForCheck) && !foundOpponent) {
                    //qDebug() << "       opponent found at: " << currentIndex;
                    foundOpponent = true;
                    r += dr[dir];
                    c += dc[dir];
                }
                else {
                    //qDebug() << "       your soldier or opponent at " << currentIndex << ", go to next iteration";
                    break;
                }
            }
        }
    }
    if(!captureAvailable) {
        return possibleMoves;
    }
    else {
        if(captureMoves.length() > 1) {
            reduceToBestKingCaptures(index, captureMoves);
        }
        return captureMoves;
    }
}
//***************************************************************************************************************************************************************************************************************************************
void GameLogic::reduceToBestKingCaptures(const QModelIndex &initialIdx, QList<QPair<char, int> > &captureMoves)
{
    QList<QPair<char, int>> bestMoves;
    int maxCaptureLength = 0;
    int currentCaptureLength = 1;
    QList<QModelIndex> indexesToCheck = QList<QModelIndex>();
    QList<QModelIndex> pathMoves = QList<QModelIndex>();
    QList<QModelIndex> checkedMoves = QList<QModelIndex>();

    for (const auto &move : captureMoves) {
        QPair<char, int> current = move;
        QModelIndex idx = m_model->indexFromPair(current);
        indexesToCheck.append(idx);
    }

    for(int idx = 0; idx < indexesToCheck.length(); idx++) {
        currentCaptureLength = 1;
        QModelIndex move = indexesToCheck.at(idx);
        QVariant currentField = m_model->data(move, CheckersModel::FieldNameRole);
        QPair<char, int> currentFieldPairValue = currentField.value<QPair<char, int>>();
        bool canContinueCapture = false;

        int row = move.row();
        int col = move.column();
        canContinueCapture = m_model->canKingContinueCaptureFrom(row, col, initialIdx, pathMoves, checkedMoves);

        if(!canContinueCapture) {
            qDebug() << "nie ma możliwości dalszego bicia";
            continue;
        }
        else {
            qDebug() << "sprawdzam dalszą ścieżkę bicia";
            int i = 0;
            //for(int i = 0; i < pathMoves.length(); i++) {
            while(i < pathMoves.length()) {
                int row = pathMoves.at(i).row();
                int col = pathMoves.at(i).column();
                canContinueCapture = m_model->canKingContinueCaptureFrom(row, col, initialIdx, pathMoves, checkedMoves);
                if(!canContinueCapture) {
                    checkedMoves.append(pathMoves.at(i));
                    pathMoves.removeAt(i);
                }
                else {
                    checkedMoves.append(pathMoves.at(i));
                    currentCaptureLength++;
                    i++;
                }
            }
        }

        if(currentCaptureLength > maxCaptureLength) {
            bestMoves.clear();
            bestMoves.append(currentFieldPairValue);
        }

        if(currentCaptureLength == maxCaptureLength) {
            bestMoves.append(currentFieldPairValue);
        }
        captureMoves = bestMoves;
    }
}
//***************************************************************************************************************************************************************************************************************************************
void GameLogic::setAllPiecesRange()
{
    for(int row = 0; row < m_rows; row++) {
        for(int col = 0; col < m_columns; col++) {
            QModelIndex index = m_model->index(row, col);
            //qDebug() << "setAllPiecesRange. index: " << index << "row: " << rowNo << "column: "<< colNo;

            if(m_model->isPiecePresent(index)) {
                bool isWhite = m_model->getPieceColor(index);
                bool isKing = m_model->getPieceType(index);

                QList <QPair <char, int> > possibleMoves;

                if(isKing) {
                    possibleMoves = getKingMoves(index, isWhite);
                }
                else {
                    possibleMoves = getManMoves(index, isWhite);
                }

                m_model->setData(index, QVariant::fromValue(possibleMoves), CheckersModel::RangeRole);
                // set captureAvailableRole :
                bool captureAvailable = isCaptureAvailable(index);
                m_model->setData(index, QVariant::fromValue(captureAvailable), CheckersModel::CaptureAvailableRole);
            }
            else {
                //qDebug() << "no piece";
                m_model->setData(index, QVariantList(), CheckersModel::RangeRole);
                m_model->setData(index, QVariant::fromValue(false), CheckersModel::CaptureAvailableRole);
                m_model->setData(index, QVariant::fromValue(false), CheckersModel::MultiCaptureRole);
            }
        }
    }
}
//***************************************************************************************************************************************************************************************************************************************
void GameLogic::resetModel()
{
    m_model->setRowCount(m_rows);
    m_model->setColumnCount(m_columns);

    //m_whiteScore = 0;
    //m_blackScore = 0;

    //Initialize board coordinates and 'black' and 'white fields
    for(int row = 0, rowCoo = 8; row < m_rows; row++, rowCoo--) {
        for(int col = 0 ; col < m_columns; col++) {
            char column = 'A' + col;

            //qDebug() << "column: " << column << "row: " << row + 1 << "rowCoo: " << rowCoo;

            QStandardItem* item = new QStandardItem();
            //qDebug()<<"item: " << item;
            m_model->setItem(row, col, item);

            QModelIndex index = m_model->index(row, col);
            //qDebug() << "index got: " << index;
            QPair<char, int> coordinates(column, rowCoo);
            bool playable = (col + row) % 2 != 0;

            m_model->setData(index, QVariant::fromValue(coordinates), CheckersModel::FieldNameRole);
            m_model->setData(index, QVariant::fromValue(playable), CheckersModel::IsPlayableRole);

            //set all fields as not selected
            //CheckersModel::selectField(index, false);
            m_model->setData(index, false, CheckersModel::CaptureAvailableRole);
            m_model->setData(index, false, CheckersModel::MultiCaptureRole);
        }
    }
    m_model->CheckersModel::deselectAllFields();
    // place the pieces on the board
    m_model->CheckersModel::initializePieces();
    // set all pieces range:
    setAllPiecesRange();
}
//***************************************************************************************************************************************************************************************************************************************
void GameLogic::initializePieces()
{
/*
    //SET BLACK PIECES:
    for(int row = 0; row < m_pieceRows; row++ ) {
        for(int col = 0; col < m_columns; col++) {
            QModelIndex index = m_model.index(row, col);
            QVariant playable = m_model.data(index, CheckersRoles::IsPlayableRole);
            if(playable.toBool()){
                CheckersModel::setPiece(index, Player::black);
                m_blackScore++;
            }
            else {
                CheckersModel::setEmptyField(index);
                m_whiteScore++;
            }
        }
    }

    //SET WHITE PIECES:
    for(int row = m_rows - 1; row >= m_rows - m_pieceRows; row--){
        for(int col = 0; col < m_columns; col++) {
            QModelIndex index = m_model.index(row, col);
            QVariant playable = m_model.data(index, CheckersRoles::IsPlayableRole);
            if(playable.toBool()){
                CheckersModel::setPiece(index, Player::white);
            }
            else {
                CheckersModel::setEmptyField(index);
            }
        }
    }
    //SET EMPTY PIECES:
    for(int row = m_pieceRows; row < m_rows - m_pieceRows; row++) {
        for(int col = 0; col < m_columns; col++) {
            QModelIndex index = m_model.index(row, col);
            CheckersModel::setEmptyField(index);
        }
    }
*/
}
//***************************************************************************************************************************************************************************************************************************************
