#include "checkersmodel.h"
//***************************************************************************************************************************************************************************************************************************************
CheckersModel::CheckersModel()
{

}
//***************************************************************************************************************************************************************************************************************************************
bool CheckersModel::isPiecePresent(const QModelIndex &index)
{
    auto pieceRole = data(index, PieceRole);
    //qDebug() << "isPiecePresent function, pieceRole: " << pieceRole;

    auto piece = pieceRole.value<Piece>();
    //qDebug() << "isPiecePresent function, piecePair: " << piecePair;

    CheckersModel::Type type = piece.type;

    //qDebug() << "isPiecePresent function, player:" << player;

    return type != CheckersModel::Type::null;
}
//***************************************************************************************************************************************************************************************************************************************
bool CheckersModel::getPieceColor(const QModelIndex &index)                                     //return true: player == white
{                                                                                               //      false: player == black
    auto pieceRole = data(index, PieceRole);
    //qDebug() << "GetPieceColor function, pieceRole: " << pieceRole;

    //auto piecePair = pieceRole.value<std::pair<CheckersModel::Player, CheckersModel::Type>>();
    auto piece = pieceRole.value<Piece>();
    //qDebug() << "isPiecePresent function, piecePair: " << piecePair;

    CheckersModel::Player player = piece.player;

    //qDebug() << "isPiecePresent function, player:" << player;

    return player == CheckersModel::Player::white;
}
//***************************************************************************************************************************************************************************************************************************************
bool CheckersModel::getPieceType(const QModelIndex &index)                                      //return true: type == king
{                                                                                               //      false: type == man
    auto pieceRole = data(index, PieceRole);
    auto piece = pieceRole.value<Piece>();

    CheckersModel::Type type = piece.type;

    return type == CheckersModel::Type::king;
}
//***************************************************************************************************************************************************************************************************************************************
int CheckersModel::getColumnsNo()
{
    return m_columns;
}
//***************************************************************************************************************************************************************************************************************************************
int CheckersModel::getRowsNo()
{
    return m_rows;
}
//***************************************************************************************************************************************************************************************************************************************
int CheckersModel::getPieceRows()
{
    return m_pieceRows;
}
//***************************************************************************************************************************************************************************************************************************************
bool CheckersModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid()) {
        //qDebug() << "setData() !index.isValid()";
        return false;
    }

    QStandardItem *item = m_model.itemFromIndex(index);

    if (!item) {
        //qDebug() << "!item";
        return false;
    }

    switch(role) {
        case CheckersRoles::FieldNameRole: {
            //qDebug() << "CoordinateRole:" << value;
            item->setData(value, FieldNameRole);
            break;
        }
        case CheckersRoles::IsPlayableRole: {
            //qDebug() << "IsPlayableRole" << value;
            item->setData(value, IsPlayableRole);
            break;
        }
        case CheckersRoles::PieceRole: {
            //qDebug() << "PieceRole";
            item->setData(value, PieceRole);
            break;
        }
        case CheckersRoles::RangeRole: {
            //qDebug() << "RangeRole";
            item->setData(value, RangeRole);
            break;
        }
        case CheckersRoles::CaptureAvailableRole: {
            //qDebug() << "CaptureAvailableRole";
            item->setData(value, CaptureAvailableRole);
            break;
        }
        case CheckersRoles::MultiCaptureRole: {
            //qDebug() << "MultiCaptureRole";
            item->setData(value, MultiCaptureRole);
            break;
        }
        case CheckersRoles::IsSelectedRole: {
            //qDebug() << "IsSelectedRole";
            item->setData(value, IsSelectedRole);
            break;
        }
        case CheckersRoles::FieldCoordinatesRole: {
            //qDebug() << "fieldCoordinatesRole";
            item->setData(value, FieldCoordinatesRole);
            break;
        }
        case CheckersRoles::FieldCenterRole: {
            //qDebug() << "fieldCenterRole";
            item->setData(value, FieldCenterRole);
            break;
        }
        case CheckersRoles::PieceCoordinatesRole: {
            //qDebug() << "PieceCoordinatesRole";
            item->setData(value, PieceCoordinatesRole);
            break;
        }
        default: {
            //qDebug() << "Default Role";
            break;
        }
    }
    //qDebug() << "emit data changed";
    emit dataChanged(index, index, {role});
    return true;
}
//***************************************************************************************************************************************************************************************************************************************
QVariant CheckersModel::data(const QModelIndex &index, int role) const
{
    //qDebug() << "index in data function: " << index;

    if (!index.isValid()) {
        //qDebug() << "function CheckersModel::data: index is not valid";
        return QVariant();
    }
    else {
        //qDebug() << "index is valid";
    }

    const QStandardItem *item = m_model.itemFromIndex(index);

    //qDebug() << "itemFromIndex: " << item;

    if (!item) {
        return QVariant();
    }

    switch(role) {
        case CheckersRoles::FieldNameRole: {
            return item->data(FieldNameRole);
        }
        case CheckersRoles::IsPlayableRole: {
            return item->data(IsPlayableRole);
        }
        case CheckersRoles::PieceRole: {
            return item->data(PieceRole);
        }
        case CheckersRoles::RangeRole: {
            return item->data(RangeRole);
        }
        case CheckersRoles::CaptureAvailableRole: {
            return item->data(CaptureAvailableRole);
        }
        case CheckersRoles::MultiCaptureRole: {
            return item->data(MultiCaptureRole);
        }
        case CheckersRoles::IsSelectedRole: {
            return item->data(IsSelectedRole);
        }
        case CheckersRoles::FieldCoordinatesRole: {
            return item->data(FieldCoordinatesRole);
        }
        case CheckersRoles::FieldCenterRole: {
            return item->data(FieldCenterRole);
        }
        case CheckersRoles::PieceCoordinatesRole: {
            return item->data(PieceCoordinatesRole);
        }
        default: {
             return QVariant();
        }
    }
    return QVariant();
}
//***************************************************************************************************************************************************************************************************************************************
void CheckersModel::setItem(int row, int col, QStandardItem *item)
{
    m_model.setItem(row, col, item);
}
//***************************************************************************************************************************************************************************************************************************************
QModelIndex CheckersModel::index(int row, int column, const QModelIndex &parent) const
{
    if(!m_model.hasIndex(row, column)) {
        //qDebug() << "index is not valid";
        return QModelIndex();
    }
    else {
        //qDebug() << "index is valid";
        //return CheckersModel::createIndex(row, column);
        return m_model.index(row, column, parent);
    }
}
//***************************************************************************************************************************************************************************************************************************************
QModelIndex CheckersModel::getIndex(int row, int column)
{
    return m_model.index(row, column);
}
//***************************************************************************************************************************************************************************************************************************************
void CheckersModel::printModel()
{
    int rowCount = m_model.rowCount();
    int columnCount = m_model.columnCount();

    for (int row = 0; row < rowCount; row++) {
        for (int col = 0; col < columnCount; col++) {
            //char column = 'A' + col;
            QModelIndex index = m_model.index(row, col);
            QVariant coordinate = m_model.data(index, CheckersRoles::FieldNameRole);
            QVariant playable = m_model.data(index, CheckersRoles::IsPlayableRole);
            QVariant piece = m_model.data(index, CheckersRoles::PieceRole);
            QVariant range = m_model.data(index, CheckersModel::RangeRole);
            //QVariant selected = m_model.data(index, CheckersRoles::IsSelectedRole);
            QVariant fieldCoords = m_model.data(index, CheckersModel::FieldCoordinatesRole);
            QVariant fieldCenter = m_model.data(index, CheckersModel::FieldCenterRole);
            QVariant pieceCoords = m_model.data(index, CheckersModel::PieceCoordinatesRole);
            qDebug() << "\nRow: " << row << ", Column: " << col << "\n"/*
                     << " Coordinate: " << coordinate
                     << ", Playable: " << playable */
                     << "\n     Piece:" << piece /*
                     << "\n     Range: " << range
                     << "\n     Selected: " << selected
                     << "\n     Index: " << index*/
                     << "\n     fieldCoords: " << fieldCoords
                     << "\n     FieldCenter: " << fieldCenter
                     << "\n     pieceCoords: " << pieceCoords
                     << "\n";
        }
    }
}
//***************************************************************************************************************************************************************************************************************************************
void CheckersModel::setTurn()
{
    m_turn == Player::black ? m_turn = Player::white : m_turn = Player::black;
}
//***************************************************************************************************************************************************************************************************************************************
CheckersModel::Player CheckersModel::getTurn()
{
    return m_turn;
}
//***************************************************************************************************************************************************************************************************************************************
QStandardItem* CheckersModel::getItem(QModelIndex index)
{
    return m_model.itemFromIndex(index);
}
//***************************************************************************************************************************************************************************************************************************************
void CheckersModel::selectField(QModelIndex index, bool selected)
{
    setData(index, QVariant::fromValue(selected), IsSelectedRole);
}
//***************************************************************************************************************************************************************************************************************************************
void CheckersModel::deselectAllFields()
{
    for(int i = 0; i < m_columns; i++) {
        for(int j = 0; j < m_rows; j++) {
            QModelIndex index = m_model.index(j, i);
            m_model.setData(index, false, IsSelectedRole);
        }
    }
}
//***************************************************************************************************************************************************************************************************************************************
void CheckersModel::updateFieldsCoordinates(const QVariantList &fieldsCoordinates)
{
    //qDebug() << "updateFieldsCoordinates function";
    //qDebug() << "fieldsCoordinates size: " << fieldsCoordinates.size();

    m_fieldsCoordinates.clear();
    m_fieldsCoordinates.resize(fieldsCoordinates.size() / 8);

    for (int i = 0, j = 0; i < fieldsCoordinates.size(); i += 8, j ++) {
        //qDebug() << "Item no. " << i / 8 <<  ": ";
        //qDebug() << "  topLeft: x:" << fieldsCoordinates[i] << "y:" << fieldsCoordinates[i + 1];
        //qDebug() << "  topRight: x:" << fieldsCoordinates[i + 2] << "y:" << fieldsCoordinates[i + 3];
        //qDebug() << "  bottomLeft: x:" << fieldsCoordinates[i + 4] << "y:" << fieldsCoordinates[i + 5];
        //qDebug() << "  bottomRight: x:" << fieldsCoordinates[i + 6] << "y:" <<  fieldsCoordinates[i + 7];
        //m_fieldsCoordinates[j].topLeft {fieldsCoordinates[i], fieldsCoordinates[i + 1]};
        CornersCoordinates coords;

        coords.topLeft = QPointF(fieldsCoordinates[i].toDouble(), fieldsCoordinates[i + 1].toDouble());
        coords.topRight = QPointF(fieldsCoordinates[i + 2].toDouble(), fieldsCoordinates[i + 3].toDouble());
        coords.bottomLeft = QPointF(fieldsCoordinates[i + 4].toDouble(), fieldsCoordinates[i + 5].toDouble());
        coords.bottomRight = QPointF(fieldsCoordinates[i + 6].toDouble(), fieldsCoordinates[i + 7].toDouble());

        m_fieldsCoordinates[j] = coords;

        // Debugowanie
        //qDebug() << "Item no." << i / 8 << ":";
        //qDebug() << "  topLeft: x:" << coords.topLeft.x() << "y:" << coords.topLeft.y();
        //qDebug() << "  topRight: x:" << coords.topRight.x() << "y:" << coords.topRight.y();
        //qDebug() << "  bottomLeft: x:" << coords.bottomLeft.x() << "y:" << coords.bottomLeft.y();
        //qDebug() << "  bottomRight: x:" << coords.bottomRight.x() << "y:" << coords.bottomRight.y();
    }
/*
    qDebug() << "Start debug m_fieldsCoordinates: ";

    for (int i = 0; i < m_fieldsCoordinates.size(); i++) {
        qDebug() << "item " << i << ": ";
        qDebug() << "   topLeft: " << m_fieldsCoordinates[i].topLeft;
        qDebug() << "   topRight: " << m_fieldsCoordinates[i].topRight;
        qDebug() << "   bottomLeft: " << m_fieldsCoordinates[i].bottomLeft;
        qDebug() << "   bottomRight: " << m_fieldsCoordinates[i].bottomRight;
    }
*/
    setFieldsCoordinatesRole();
    setFieldCenterRole();

    //qDebug() << "m_fieldsCoordinates size: " << m_fieldsCoordinates.size();
    //qDebug() << "end of updateFieldsCoordinates function";
}
//***************************************************************************************************************************************************************************************************************************************
void CheckersModel::updatePiecesCoordinates(const QVariantList &piecesCoordinates)
{
    //qDebug() << "updatePiecesCoordinates function";
    //qDebug() << "piecesCoordinates size: " << piecesCoordinates.size();

    m_piecesCoordinates.clear();
    m_piecesCoordinates.resize(piecesCoordinates.size() / 8);

    for (int i = 0, j = 0; i < piecesCoordinates.size(); i += 8, j ++) {
        //qDebug() << "Item no. " << i / 8 <<  ": ";
        //qDebug() << "  topLeft: x:" << fieldsCoordinates[i] << "y:" << fieldsCoordinates[i + 1];
        //qDebug() << "  topRight: x:" << fieldsCoordinates[i + 2] << "y:" << fieldsCoordinates[i + 3];
        //qDebug() << "  bottomLeft: x:" << fieldsCoordinates[i + 4] << "y:" << fieldsCoordinates[i + 5];
        //qDebug() << "  bottomRight: x:" << fieldsCoordinates[i + 6] << "y:" <<  fieldsCoordinates[i + 7];
        //m_fieldsCoordinates[j].topLeft {fieldsCoordinates[i], fieldsCoordinates[i + 1]};
        CornersCoordinates coords;

        coords.topLeft = QPointF(piecesCoordinates[i].toDouble(), piecesCoordinates[i + 1].toDouble());
        coords.topRight = QPointF(piecesCoordinates[i + 2].toDouble(), piecesCoordinates[i + 3].toDouble());
        coords.bottomLeft = QPointF(piecesCoordinates[i + 4].toDouble(), piecesCoordinates[i + 5].toDouble());
        coords.bottomRight = QPointF(piecesCoordinates[i + 6].toDouble(), piecesCoordinates[i + 7].toDouble());

        m_piecesCoordinates[j] = coords;

        //qDebug() << "Item no." << i / 8 << ":";
        //qDebug() << "  topLeft: x:" << coords.topLeft.x() << "y:" << coords.topLeft.y();
        //qDebug() << "  topRight: x:" << coords.topRight.x() << "y:" << coords.topRight.y();
        //qDebug() << "  bottomLeft: x:" << coords.bottomLeft.x() << "y:" << coords.bottomLeft.y();
        //qDebug() << "  bottomRight: x:" << coords.bottomRight.x() << "y:" << coords.bottomRight.y();
    }
/*
    qDebug() << "Start debug m_piecesCoordinates: ";

    for (int i = 0; i < m_piecesCoordinates.size(); i++) {
        qDebug() << "item " << i << ": ";
        qDebug() << "   topLeft: " << m_piecesCoordinates[i].topLeft;
        qDebug() << "   topRight: " << m_piecesCoordinates[i].topRight;
        qDebug() << "   bottomLeft: " << m_piecesCoordinates[i].bottomLeft;
        qDebug() << "   bottomRight: " << m_piecesCoordinates[i].bottomRight;
    }
*/
    setPiecesCoordinatesRole();
    //setFieldCenterRole();

    //qDebug() << "m_piecesCoordinates size: " << m_piecesCoordinates.size();
    //qDebug() << "end of updatePiecesCoordinates function";
}
//***************************************************************************************************************************************************************************************************************************************
void CheckersModel::removePiece(QModelIndex from, QModelIndex to)
{
    qDebug() << "capture! remove pieces between: " << from << " and " << to;

    bool isKing = getPieceType(from);
    qDebug() << "isKing: " << isKing;

    if(!isKing) {
        qDebug() << "man captures";
        //znajdź większy index dla row i column:
        int maxRow = std::max(from.row(), to.row());
        int maxCol = std::max(from.column(), to.column());
        int minRow = std::min(from.row(), to.row());
        int minCol = std::min(from.column(), to.column());

        qDebug() << "maxRow: " << maxRow << ", minRow: " << minRow;
        qDebug() << "maxCol: " << maxCol << ", minCol: " << minCol;

        //nie wiem, czy to rozwiązanie jest na dłużej, ale w pewnych okolicznościach usuwało pionki
        //gdy różnica między kolumnami/rzędami wynosiła 1, stąd poniższa instrukcja "if":

        if(maxRow - minRow < 2 || maxCol - minCol < 2) {
            return;
        }

        int removeRow = (from.row() + to.row()) / 2;
        int removeCol = (from.column() + to.column()) / 2;

        QModelIndex indexToRemove = getIndex(removeRow, removeCol);
        qDebug() << "indexToRemove (MAN): " << indexToRemove;

        setEmptyField(indexToRemove);
    }
    else {
        qDebug() << "king captures";
        int fromRow = from.row();
        int fromCol = from.column();
        int toRow = to.row();
        int toCol = to.column();

        int dRow = (toRow - fromRow) > 0 ? 1 : -1;
        int dCol = (toCol - fromCol) > 0 ? 1 : -1;

        int row = fromRow + dRow;
        int col = fromCol + dCol;

        while (row != toRow && col != toCol) {
            QModelIndex current = getIndex(row, col);

            if (isPiecePresent(current)) {
                // Znaleziono figurę przeciwnika do zbicia
                qDebug() << "indexToRemove (KING): " << current;
                setEmptyField(current);
                return;
            }

            row += dRow;
            col += dCol;
        }
    }

    if(getPieceColor(from)) {
        m_blackScore--;
    }
    else {
        m_whiteScore--;
    }
}
//***************************************************************************************************************************************************************************************************************************************
QModelIndex CheckersModel::getModelIndexFromGivenCoordinates(double averageX, double averageY)
{
    //qDebug() << "getModelIndexFromGivenCoordinates function: ";

    for (int row = 0; row < m_rows; row++) {
        for (int col = 0; col < m_columns; col++) {
            QModelIndex index = m_model.index(row, col);
            CornersCoordinates corners = data(index, FieldCoordinatesRole).value<CornersCoordinates>();
            //qDebug() << "   corners: " << corners;

            if (averageX >= corners.topLeft.x()        &&
                averageX <= corners.topRight.x()       &&
                averageY >= corners.topLeft.y()        &&
                averageY <= corners.bottomLeft.y())     {
                return index;
            }
        }
    }

    return QModelIndex();
}
//***************************************************************************************************************************************************************************************************************************************
void CheckersModel::setColumns(int col)
{
    if(col % 2 != 0) {
        //qDebug() << "the number of columns must be even. Added col + 1";                    // needs create even validation
        col++;
        CheckersModel::setColumns(col);
    }
    else {
        m_columns = col;
    }
}
//***************************************************************************************************************************************************************************************************************************************
void CheckersModel::setRows(int row)
{
    if(row % 2 != 0) {
        //qDebug() << "the number of rows must be even. Added row + 1";
        row++;
        CheckersModel::setRows(row);
    }
    else {
        m_rows = row;
    }
}
//***************************************************************************************************************************************************************************************************************************************
void CheckersModel::setPieceRows(int row)
{
    int maxPieceRows = (m_rows - 2) / 2;

    if(row > maxPieceRows) {
        //qDebug() << "to many piece rows. Setting to maximum allowed: " << maxPieceRows;
        m_pieceRows = maxPieceRows;
    }
    else {
        //qDebug() << "set " << row << " pieces rows";
        m_pieceRows = row;
    }
}
//***************************************************************************************************************************************************************************************************************************************
void CheckersModel::setPiece(QModelIndex index, Player player, Type type)
{
    Piece piece;
    piece.player = player;
    piece.type = type;

    setData(index, QVariant::fromValue(piece), PieceRole);
}
//***************************************************************************************************************************************************************************************************************************************
void CheckersModel::setEmptyField(QModelIndex index)
{
    Player player = Player::null;
    Type type = Type::null;

    Piece piece;
    piece.player = player;
    piece.type = type;

    setData(index, QVariant::fromValue(piece), PieceRole);
}
//***************************************************************************************************************************************************************************************************************************************
void CheckersModel::showScore()
{
    qDebug() << "white score: " << m_whiteScore;
    qDebug() << "black score: " << m_blackScore;
}
//***************************************************************************************************************************************************************************************************************************************
void CheckersModel::setFieldsCoordinatesRole()
{
    int fieldsNo = m_columns * m_rows;
    //qDebug() << "function setFieldsCoordinatesRole: ";

    if(fieldsNo != m_fieldsCoordinates.size()) {
        //qDebug() << "   m_fieldsCoordinates size not equal model size. Return";
        return;
    }
    else {
        //qDebug() << "   m_fieldsCoordinates size equals model size. Start append model FieldCoordinatesRole";
        for(int row = 0, arrayIdx = 0; row < m_rows; row++) {
            for(int column = 0; column < m_columns; column++) {
                QModelIndex index = getIndex(row, column);
                setData(index, QVariant::fromValue(m_fieldsCoordinates[arrayIdx]), FieldCoordinatesRole);
                arrayIdx++;
            }
        }
    }
}
//***************************************************************************************************************************************************************************************************************************************
void CheckersModel::setFieldCenterRole()
{
    int fieldsNo = m_columns * m_rows;
    //qDebug() << "function setFieldCenterRole: ";

    if(fieldsNo != m_fieldsCoordinates.size()) {
        //qDebug() << "   m_fieldsCoordinates size not equal model size. Return";
        return;
    }
    else {
        //qDebug() << "   m_fieldsCoordinates size equals model size. Start append model PieceCenterRole";
        for(int row = 0, arrayIdx = 0; row < m_rows; row++) {
            for(int column = 0; column < m_columns; column++) {
                QModelIndex index = getIndex(row, column);
                QVariant isPlayable = data(index, IsPlayableRole);
                if(!isPlayable.toBool() ) {
                    setData(index, QVariant::fromValue(QPointF(-1, -1)), FieldCenterRole);
                }
                else {
                    double averageX = (m_fieldsCoordinates[arrayIdx].topLeft.x() + m_fieldsCoordinates[arrayIdx].topRight.x() + m_fieldsCoordinates[arrayIdx].bottomLeft.x() + m_fieldsCoordinates[arrayIdx].bottomRight.x()) / 4;
                    double averageY = (m_fieldsCoordinates[arrayIdx].topLeft.y() + m_fieldsCoordinates[arrayIdx].topRight.y() + m_fieldsCoordinates[arrayIdx].bottomLeft.y() + m_fieldsCoordinates[arrayIdx].bottomRight.y()) / 4;
                    QPointF fieldCenter = {averageX, averageY};
                    //qDebug() << "index: " << arrayIdx << "fieldCenter: " << fieldCenter;
                    setData(index, QVariant::fromValue(fieldCenter), FieldCenterRole);
                }
                arrayIdx++;
            }
        }
    }
}
//***************************************************************************************************************************************************************************************************************************************
void CheckersModel::setPiecesCoordinatesRole()
{
    int fieldsNo = m_columns * m_rows;
    //qDebug() << "function setPiecesCoordinatesRole: ";

    if(fieldsNo != m_piecesCoordinates.size()) {
        //qDebug() << "   m_piecesCoordinates size not equal model size. Return";
        return;
    }
    else {
        //qDebug() << "   m_piecesCoordinates size equals model size. Start append model PiecesCoordinatesRole";
        for(int row = 0, arrayIdx = 0; row < m_rows; row++) {
            for(int column = 0; column < m_columns; column++) {
                QModelIndex index = getIndex(row, column);
                setData(index, QVariant::fromValue(m_piecesCoordinates[arrayIdx]), PieceCoordinatesRole);
                arrayIdx++;
            }
        }
    }
}
//***************************************************************************************************************************************************************************************************************************************
QModelIndex CheckersModel::findFieldIndexForPieceCenter(const QPointF &pieceCenter)
{
    qDebug() << "findFieldIndexForPieceCenter function: ";

    int count = 0;

    for (int row = 0; row < m_rows; row++) {
        for (int col = 0; col < m_columns; col++) {

            QModelIndex fieldIndex = getIndex(row, col);
            CornersCoordinates fieldCorners = data(fieldIndex, FieldCoordinatesRole).value<CornersCoordinates>();
/*
            qDebug() << count;
            qDebug() << "   field name: " << data(fieldIndex, FieldNameRole);
            qDebug() << "   piece center x: " << pieceCenter.x();
            qDebug() << "   piece center y: " << pieceCenter.y();
            qDebug() << "   topLeft.x: " << fieldCorners.topLeft.x();
            qDebug() << "   bottomRight.x: " << fieldCorners.bottomRight.x();
            qDebug() << "   bottomLeft.y: " << fieldCorners.bottomLeft.y();
            qDebug() << "   topRight.y: " << fieldCorners.topRight.y();
*/
            if (pieceCenter.x() >= fieldCorners.topLeft.x() &&
                pieceCenter.x() <= fieldCorners.bottomRight.x() &&
                pieceCenter.y() >= fieldCorners.topLeft.y() &&
                pieceCenter.y() <= fieldCorners.bottomRight.y()) {
                qDebug() << "FIELD INDEX FOR PIECE CENTER FOUND: " << data(fieldIndex, FieldNameRole);
                return fieldIndex;
            }

            count++;
        }
    }
    qDebug() << "WARNING: fieldindex for piece center not found !";
    return QModelIndex();
}
//***************************************************************************************************************************************************************************************************************************************
QModelIndex CheckersModel::indexFromPair(const QPair<char, int> &pos) const
{
    int col = pos.first - 'A';      // 'A' -> 0, 'B' -> 1, ..., 'H' -> 7
    int row = 8 - pos.second;       // 8 -> 0, 7 -> 1, ..., 1 -> 7
    return m_model.index(row, col);
}
//***************************************************************************************************************************************************************************************************************************************
bool CheckersModel::isInsideBoard(int row, int col)
{
    return (row >= 0 && row < 8 && col >= 0 && col < 8);
}
//***************************************************************************************************************************************************************************************************************************************
CheckersModel::Player CheckersModel::getPlayerForCheck(const QModelIndex &index)
{
    Player playerForCheck;

    if(getPieceColor(index)) {
        return playerForCheck = Player::white;
    }
    else {
        return playerForCheck = Player::black;
    }
}
//***************************************************************************************************************************************************************************************************************************************
QDebug operator<<(QDebug debug, const CornersCoordinates &coords) {
    debug.nospace() << "CornersCoordinates("
                    << "topLeft: " << coords.topLeft
                    << ", topRight: " << coords.topRight
                    << ", bottomLeft: " << coords.bottomLeft
                    << ", bottomRight: " << coords.bottomRight
                    << ")";
    return debug.space();
}
//**************************************************************************************************************************************************************************************************************************************
QDebug operator<<(QDebug debug, const Piece &pieceRole) {
    debug.nospace() << "Piece("
                    << "player: " << pieceRole.player
                    << ", type: " << pieceRole.type
                    << ")";
    return debug.space();
}
//**************************************************************************************************************************************************************************************************************************************
