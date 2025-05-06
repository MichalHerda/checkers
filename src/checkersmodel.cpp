#include "checkersmodel.h"
//***************************************************************************************************************************************************************************************************************************************
CheckersModel::CheckersModel()
{
    /*
    m_rolesMetaEnum = QMetaEnum::fromType<CheckersRoles>();

    for(int i = 0; i < m_rolesMetaEnum.keyCount(); i++) {
        auto s = QString(m_rolesMetaEnum.key(i));
        qDebug() << "roles map: " << QByteArray(s.replace(0,1,s[0].toLower()).toUtf8());
        m_rolesMap.insert(
            m_rolesMetaEnum.value(i),
            QByteArray(s.replace(0,1,s[0].toLower()).toUtf8())
        );
    }
    */
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

    //return player != CheckersModel::Type::null;
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
    //auto piecePair = pieceRole.value<std::pair<CheckersModel::Player, CheckersModel::Type>>();
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
void CheckersModel::resetModel()
{
    m_model.setRowCount(m_rows);
    m_model.setColumnCount(m_columns);

    m_whiteScore = 0;
    m_blackScore = 0;

    //Initialize board coordinates and 'black' and 'white fields
    for(int row = 0, rowCoo = 8; row < m_rows; row++, rowCoo--) {
        for(int col = 0 ; col < m_columns; col++) {
            char column = 'A' + col;

            //qDebug() << "column: " << column << "row: " << row + 1 << "rowCoo: " << rowCoo;

            QStandardItem* item = new QStandardItem();
            //qDebug()<<"item: " << item;
            m_model.setItem(row, col, item);

            QModelIndex index = m_model.index(row, col);
            //qDebug() << "index got: " << index;
            QPair<char, int> coordinates(column, rowCoo);
            bool playable = (col + row) % 2 != 0;

            setData(index, QVariant::fromValue(coordinates), FieldNameRole);
            setData(index, QVariant::fromValue(playable), IsPlayableRole);

            //set all fields as not selected
            //CheckersModel::selectField(index, false);
            setData(index, false, CaptureAvailableRole);
            setData(index, false, MultiCaptureRole);
        }
    }
    CheckersModel::deselectAllFields();
    // place the pieces on the board
    CheckersModel::initializePieces();
    // set all pieces range:
    CheckersModel::setAllPiecesRange();
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
QModelIndex CheckersModel::index(int row, int column, const QModelIndex &parent) const
{
    if(!m_model.hasIndex(row, column)) {
        //qDebug() << "index is not valid";
        return QModelIndex();
    }
    else {
        //qDebug() << "index is valid";
        return CheckersModel::createIndex(row, column);
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
/*
QHash<int, QByteArray> CheckersModel::roleNames() const
{
    qDebug() << "roleNames called";

    QHash<int, QByteArray> roles;
    roles[FieldNameRole] = "FieldNameRole";
    roles[IsPlayableRole] = "isPlayableRole";
    roles[PieceRole] = "pieceRole";
    roles[RangeRole] = "rangeRole";
    roles[CaptureAvailableRole] = "captureAvailableRole";
    roles[MultiCaptureRole] = "multiCaptureRole";
    roles[IsSelectedRole] = "isSelectedRole";

    return m_rolesMap;
}
*/
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
bool CheckersModel::isMoveValid(QModelIndex index, double averageX, double averageY)
{
    qDebug() << "isMoveValid, index passed: " << index;
    QVariantList range = data(index, RangeRole).toList();
    qDebug() << "passed index range: "  << range;

    auto hasCapture = m_model.data(index, CaptureAvailableRole);
    if(!hasCapture.toBool() && mustCapture(player)) {
        return false;
    }

    QPointF pieceCenter(averageX, averageY);
    QModelIndex targetFieldIndex = CheckersModel::findFieldIndexForPieceCenter(pieceCenter);
    qDebug() << "piece center is now inside field: " << targetFieldIndex;

    std::pair<char, int> targetCoordinate = data(targetFieldIndex, FieldNameRole).value<std::pair<char, int>>();
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
void CheckersModel::initializePieces()
{
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
                //Player player = Player::null;
                //Type type = Type::null;
                //Piece piece;
                //piece.player = Player::null;
                //piece.type = Type::null;
                //setData(index, QVariant::fromValue(piece), PieceRole);
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
}
//***************************************************************************************************************************************************************************************************************************************
void CheckersModel::setPiece(QModelIndex index, Player player, Type type)
{
    //Player playerToSet = player;
    //Type typeToSet = type;

    //QPair<Player, Type> piece(playerToSet, typeToSet);

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
void CheckersModel::setAllPiecesRange()
{
    for(int row = 0; row < m_rows; row++) {
        for(int col = 0; col < m_columns; col++) {
            QModelIndex index = m_model.index(row, col);
            //int rowNo = index.row();
            //int colNo = index.column();
            //qDebug() << "setAllPiecesRange. index: " << index << "row: " << rowNo << "column: "<< colNo;

            if(isPiecePresent(index)) {
                bool isWhite = getPieceColor(index);
                bool isKing = getPieceType(index);

                QList <QPair <char, int> > possibleMoves;

                if(isKing) {
                    possibleMoves = getKingMoves(index, isWhite);
                }
                else {
                    possibleMoves = getManMoves(index, isWhite);
                }

                setData(index, QVariant::fromValue(possibleMoves), RangeRole);
                // set captureAvailableRole :
                bool captureAvailable = isCaptureAvailable(index);
                setData(index, QVariant::fromValue(captureAvailable), CaptureAvailableRole);
            }
            else {
                //qDebug() << "no piece";
                setData(index, QVariantList(), RangeRole);
                setData(index, QVariant::fromValue(false), CaptureAvailableRole);
                setData(index, QVariant::fromValue(false), MultiCaptureRole);
            }
        }
    }
}
//***************************************************************************************************************************************************************************************************************************************
bool CheckersModel::mustCapture(Player player)
{
    for(int row = 0, arrayIdx = 0; row < m_rows; row++) {
        for(int column = 0; column < m_columns; column++) {
            QModelIndex index = getIndex(row, column);
            bool isWhite = getPieceColor(index);
            bool isCurrentPlayer = (player == Player::white && isWhite) || (player == Player::black && !isWhite);
            if(isCurrentPlayer) {
                bool captureAvailable = isCaptureAvailable(index);
                if(captureAvailable) {
                    return true;
                }
            }
        }
    }
    return false;
}
//***************************************************************************************************************************************************************************************************************************************
void CheckersModel::evaluatePromotionToKing(QModelIndex index)
{
    //qDebug() << "evaluate promotion to king: ";
    //qDebug() << "player: " << player;
    //qDebug() << "getPieceType: " << getPieceType(index);
    //qDebug() << "row: " << index.row();

    if(player == Player::white &&
       getPieceType(index) == false &&
       index.row() == 0) {
            qDebug() << "promote to king";
            setEmptyField(index);
            setPiece(index, player, Type::king);
    }

    if(player == Player::black &&
        getPieceType(index) == false &&
        index.row() == 7) {
            qDebug() << "promote to king";
            setEmptyField(index);
            setPiece(index, player, Type::king);
    }
}
//***************************************************************************************************************************************************************************************************************************************
void CheckersModel::showScore()
{
    qDebug() << "white score: " << m_whiteScore;
    qDebug() << "black score: " << m_blackScore;
}
//***************************************************************************************************************************************************************************************************************************************
bool CheckersModel::gameOnRead()const {
    return gameOn;
}
//***************************************************************************************************************************************************************************************************************************************
CheckersModel::Player CheckersModel::playerRead()const {
    return player;
}
//***************************************************************************************************************************************************************************************************************************************
void CheckersModel::gameOnWrite(bool _gameOn) {
    gameOn = _gameOn;
    emit gameOnChanged(_gameOn);
}
//***************************************************************************************************************************************************************************************************************************************
void CheckersModel::playerWrite(CheckersModel::Player _player) {
    player = _player;
    emit playerChanged(_player);
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
                    //QPointF fieldCenter = {-1, -1};
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
QList <QPair <char, int> > CheckersModel::getKingMoves(const QModelIndex &index, bool isWhite)
{
    qDebug() << "getKingMoves function: ";
    QList <QPair <char, int> > possibleMoves {};
    QList <QPair <char, int> > captureMoves {};

    int rowNo = index.row();
    int colNo = index.column();
    bool captureAvailable = isCaptureAvailable(index);
    Player playerForCheck = getPlayerForCheck(index);

    const int dr[] = {-1, -1, 1, 1}; // góra-lewo, góra-prawo, dół-lewo, dół-prawo
    const int dc[] = {-1, 1, -1, 1};

    for (int dir = 0; dir < 4; ++dir) {
        int r = rowNo + dr[dir];
        int c = colNo + dc[dir];
        bool foundOpponent = false;

        while (isInsideBoard(r, c)) {
            QModelIndex currentIndex = getIndex(r, c);

            if (!isPiecePresent(currentIndex)) {
                qDebug() << "   piece not present at " << currentIndex;
                if (!foundOpponent) {
                    if(!captureAvailable) {
                        qDebug() << "       opponent not found, capture not available, add: " << currentIndex;
                        QVariant move = data(currentIndex, FieldNameRole);
                        possibleMoves.push_back(move.value <QPair <char, int> > ());
                    }
                    else {
                        qDebug() << "       opponent not found, capture available, no moves to add";
                    }
                }
                else {
                    if(!captureAvailable) {
                        qDebug() << "       opponent found at " << currentIndex << ", capture available, no moves to add";
                    }
                    else {
                        qDebug() << "       opponent found, capture available, add: " << currentIndex;
                        QVariant move = data(currentIndex, FieldNameRole);
                        QPair <char, int> movePair = move.value <QPair <char, int> > ();
                        captureMoves.push_back(movePair);

                        // TODO: osobna funkcja:

                        // sprawdź, czy z pola za przeciwnikiem można kontynuować bicie
                        /*
                        int nextR = r + dr[dir];
                        int nextC = c + dc[dir];
                        if (canKingContinueCaptureFrom(nextR, nextC, index)) {
                            //possibleMoves.clear(); // Jeśli znajdziemy pole z dalszym biciem, odrzucamy wcześniejsze
                            break;
                        }
                        */
                    }
                }
                //else break;

                r += dr[dir];
                c += dc[dir];

            }
            else {
                qDebug() << "   piece present at " << currentIndex;
                if (isOpponentAt(currentIndex, playerForCheck) && !foundOpponent) {
                    qDebug() << "       opponent found at: " << currentIndex;
                    foundOpponent = true;
                    r += dr[dir];
                    c += dc[dir];
                }
                else {
                    qDebug() << "       your soldier or opponent at " << currentIndex << ", go to next iteration";
                    // Własny pionek lub już był przeciwnik — koniec kierunku
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
QList <QPair <char, int> > CheckersModel::getManMoves(const QModelIndex &index, bool isWhite)
{
    QList <QPair <char, int> > possibleMoves {};
    auto isCaptureAvailable = data(index, CaptureAvailableRole);

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
            if (isInsideBoard(newRow, newCol)) {
                QModelIndex checkIndex = getIndex(newRow, newCol);
                if (!isPiecePresent(checkIndex)) {
                    QVariant move = data(checkIndex, FieldNameRole);
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

            if (isInsideBoard(newRow, newCol) && isInsideBoard(middleRow, middleCol)) {
                QModelIndex targetIndex = getIndex(newRow, newCol);
                QModelIndex middleIndex = getIndex(middleRow, middleCol);

                if (!isPiecePresent(targetIndex)) { // cel musi być pusty
                    if (isPiecePresent(middleIndex)) { // na środku musi być pionek
                        bool middleIsWhite = getPieceColor(middleIndex);
                        if (middleIsWhite != isWhite) { // i przeciwnika
                            QVariant move = data(targetIndex, FieldNameRole);
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
void CheckersModel::reduceToBestKingCaptures(const QModelIndex &initialIdx, QList<QPair<char, int> > &captureMoves)
{
    QList<QPair<char, int>> bestMove;
    int maxCaptureLength = 0;

    for (const auto &move : captureMoves) {
        bool canContinueCapture = false;
        //do {
        //
        //}
        //while(canContinueCapture);
    }
}
//***************************************************************************************************************************************************************************************************************************************
QModelIndex CheckersModel::indexFromPair(const QPair<char, int> &pos) const
{
    int col = pos.first - 'A';      // 'A' -> 0, 'B' -> 1, ..., 'H' -> 7
    int row = 8 - pos.second;       // 8 -> 0, 7 -> 1, ..., 1 -> 7
    return m_model.index(row, col);
}
//***************************************************************************************************************************************************************************************************************************************
bool CheckersModel::isCaptureAvailable(const QModelIndex &index)
{
    if (!isPiecePresent(index)) {
        //qDebug() << "isCaptureAvailable function. Piece not present";
        return false;
    }

    bool isWhite = getPieceColor(index);
    bool isKing = getPieceType(index);

    Player playerForCheck = getPlayerForCheck(index);

    int row = index.row();
    int col = index.column();

    const int dr[] = {-1, -1, 1, 1}; // góra-lewo, góra-prawo, dół-lewo, dół-prawo
    const int dc[] = {-1, 1, -1, 1};

    if (isKing) {
        qDebug() << "isCaptureAvailable Role KING, index: " << index << "player for check: " << playerForCheck;
        for (int dir = 0; dir < 4; ++dir) {
            int r = row + dr[dir];
            int c = col + dc[dir];
            bool foundOpponent = false;
            QModelIndex opponentIdx = QModelIndex();
            while (isInsideBoard(r, c)) {
                qDebug() << "r: " << r;
                qDebug() << "c: " << c;
                QModelIndex nextIdx = m_model.index(r, c);
                if (isPiecePresent(nextIdx) && !foundOpponent) {
                    if (isOpponentAt(nextIdx, playerForCheck)) {
                            qDebug() << "opponent found at: " << nextIdx;
                            opponentIdx = nextIdx;
                            foundOpponent = true;
                    }
                    else {
                            qDebug() << "your soldier found at: " << nextIdx;
                            break;
                    }
                    //else break;
                }
                else {
                    if (foundOpponent) {
                        int checkR = opponentIdx.row() + dr[dir];
                        int checkC = opponentIdx.column() + dc[dir];
                        QModelIndex checkIdx = m_model.index(checkR, checkC);
                        qDebug() << "nextIdx: " << checkIdx << "row: " << r << "column: " << c;
                        if (isInsideBoard(r, c) &&
                            !isPiecePresent(nextIdx) ) {
                                qDebug() << "empty field found: " << nextIdx << ", capture available for king";
                                return true;
                        }
                        else if ( (isInsideBoard(r,c)) &&
                                   isPiecePresent(nextIdx) ) {
                                        qDebug() << "piece present, cannot move " << nextIdx;
                                        break;
                        }
                        else {
                            qDebug() << "neither empty field found nor piece present";
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

            if (isInsideBoard(landR, landC)) {
                QModelIndex midIdx = m_model.index(midR, midC);
                QModelIndex landIdx = m_model.index(landR, landC);

                if (isPiecePresent(midIdx) &&
                    getPieceColor(midIdx) != isWhite &&
                    !isPiecePresent(landIdx)) {
                    return true;
                }
            }
        }
    }

    return false;
}
//***************************************************************************************************************************************************************************************************************************************
bool CheckersModel::isInsideBoard(int row, int col)
{
    return (row >= 0 && row < 8 && col >= 0 && col < 8);
}
//***************************************************************************************************************************************************************************************************************************************
bool CheckersModel::canKingContinueCaptureFrom(int row, int col, QModelIndex initialKingIdx)
{
    const int dr[] = {-1, -1, 1, 1};
    const int dc[] = {-1, 1, -1, 1};

    Player playerForCheck = getPlayerForCheck(initialKingIdx);

    for (int dir = 0; dir < 4; ++dir) {
        int r = row + dr[dir];
        int c = col + dc[dir];
        bool foundOpponent = false;

        while (isInsideBoard(r, c)) {
            QModelIndex currentIndex = getIndex(r, c);

            if (!isPiecePresent(currentIndex)) {
                if (foundOpponent) {
                    return true; // Jest przeciwnik i wolne pole za nim
                }
                r += dr[dir];
                c += dc[dir];
            }
            else {
                if (isOpponentAt(currentIndex, playerForCheck) && !foundOpponent) {
                    foundOpponent = true;
                    r += dr[dir];
                    c += dc[dir];
                }
                else {
                    break;
                }
            }
        }
    }
    return false;
}
//***************************************************************************************************************************************************************************************************************************************
bool CheckersModel::isOpponentAt(const QModelIndex &index, Player playerForCheck)
{
    return ( (playerForCheck == Player::white)  &&  (!getPieceColor(index)) ) ||
           ( (playerForCheck == Player::black)  &&  ( getPieceColor(index)) );
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
