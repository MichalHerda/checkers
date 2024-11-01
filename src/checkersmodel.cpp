#include "checkersmodel.h"

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

bool CheckersModel::isPiecePresent(const QModelIndex &index)
{
    auto pieceRole = data(index, PieceRole);
    //qDebug() << "isPiecePresent function, pieceRole: " << pieceRole;

    auto piecePair = pieceRole.value<std::pair<CheckersModel::Player, CheckersModel::Type>>();
    //qDebug() << "isPiecePresent function, piecePair: " << piecePair;

    CheckersModel::Type type = piecePair.second;

    //qDebug() << "isPiecePresent function, player:" << player;

    //return player != CheckersModel::Type::null;
    return type != CheckersModel::Type::null;
}

bool CheckersModel::getPieceColor(const QModelIndex &index)                                     //return true: player == white
{                                                                                               //      false: player == black
    auto pieceRole = data(index, PieceRole);
    //qDebug() << "GetPieceColor function, pieceRole: " << pieceRole;

    auto piecePair = pieceRole.value<std::pair<CheckersModel::Player, CheckersModel::Type>>();
    //qDebug() << "isPiecePresent function, piecePair: " << piecePair;

    CheckersModel::Player player = piecePair.first;

    //qDebug() << "isPiecePresent function, player:" << player;

    return player == CheckersModel::Player::white;
}

bool CheckersModel::getPieceType(const QModelIndex &index)                                      //return true: type == king
{                                                                                               //      false: type == man
    auto pieceRole = data(index, PieceRole);
    auto piecePair = pieceRole.value<std::pair<CheckersModel::Player, CheckersModel::Type>>();

    CheckersModel::Type type = piecePair.second;

    return type == CheckersModel::Type::king;
}

int CheckersModel::getColumnsNo()
{
    return m_columns;
}

int CheckersModel::getRowsNo()
{
    return m_rows;
}

void CheckersModel::resetModel()
{
    m_model.setRowCount(m_rows);
    m_model.setColumnCount(m_columns);

    //Initialize board coordinates and 'black' and 'white fields
    for(int row = m_rows - 1; row >= 0; row--) {
        for(int col = 0 ; col < m_columns; col++) {
            char column = 'A' + col;

            qDebug() << "column: " << column << "row: " << row + 1;

            QStandardItem* item = new QStandardItem();
            qDebug()<<"item: " << item;
            m_model.setItem(row, col, item);

            QModelIndex index = m_model.index(row, col);
            qDebug() << "index got: " << index;
            QPair<char, int> coordinates(column, row + 1);
            bool playable = (col + row) % 2 == 0;

            setData(index, QVariant::fromValue(coordinates), CoordinatesRole);
            setData(index, QVariant::fromValue(playable), IsPlayableRole);

            //set all fields as not selected
            //CheckersModel::selectField(index, false);
        }
    }
    CheckersModel::deselectAllFields();
    // place the pieces on the board
    CheckersModel::initializePieces();
    // set all pieces range:
    CheckersModel::setAllPiecesRange();
}

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
        case CheckersRoles::CoordinatesRole: {
            qDebug() << "CoordinateRole:" << value;
            item->setData(value, CoordinatesRole);
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
        default: {
            //qDebug() << "Default Role";
            break;
        }
    }
    //qDebug() << "emit data changed";
    emit dataChanged(index, index, {role});
    return true;
}

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
        case CheckersRoles::CoordinatesRole: {
            return item->data(CoordinatesRole);
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
        default: {
             return QVariant();
        }
    }
    return QVariant();
}

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

QModelIndex CheckersModel::getIndex(int row, int column)
{
    return m_model.index(row, column);
}

void CheckersModel::printModel() {
    int rowCount = m_model.rowCount();
    int columnCount = m_model.columnCount();

    for (int col = 0; col < columnCount; col++) {
        char column = 'A' + col;
        for (int row = 0; row < rowCount; row++) {
            QModelIndex index = m_model.index(row, col);
            QVariant coordinate = m_model.data(index, CheckersRoles::CoordinatesRole);
            QVariant playable = m_model.data(index, CheckersRoles::IsPlayableRole);
            QVariant piece = m_model.data(index, CheckersRoles::PieceRole);
            QVariant range = m_model.data(index, CheckersModel::RangeRole);
            QVariant selected = m_model.data(index, CheckersRoles::IsSelectedRole);
            qDebug() << "Column: " << column << ", Row: " << row + 1 << ", Coordinate: " << coordinate << ", Playable: " << playable
                     << "Piece:" << piece << "Range: " << range << "Selected: " << selected << "Index: " << index;
        }
    }
}

/*
QHash<int, QByteArray> CheckersModel::roleNames() const
{
    qDebug() << "roleNames called";

    QHash<int, QByteArray> roles;
    roles[CoordinatesRole] = "coordinatesRole";
    roles[IsPlayableRole] = "isPlayableRole";
    roles[PieceRole] = "pieceRole";
    roles[RangeRole] = "rangeRole";
    roles[CaptureAvailableRole] = "captureAvailableRole";
    roles[MultiCaptureRole] = "multiCaptureRole";
    roles[IsSelectedRole] = "isSelectedRole";

    return m_rolesMap;
}
*/

void CheckersModel::setTurn()
{
    m_turn == Player::black ? m_turn = Player::white : m_turn = Player::black;
}

CheckersModel::Player CheckersModel::getTurn()
{
    return m_turn;
}

QStandardItem* CheckersModel::getItem(QModelIndex index)
{
    return m_model.itemFromIndex(index);
}

void CheckersModel::selectField(QModelIndex index, bool selected)
{
    setData(index, QVariant::fromValue(selected), IsSelectedRole);
}

void CheckersModel::deselectAllFields()
{
    for(int i = 0; i < m_columns; i++) {
        for(int j = 0; j < m_rows; j++) {
            QModelIndex index = m_model.index(j, i);
            m_model.setData(index, false, IsSelectedRole);
        }
    }
}

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

void CheckersModel::initializePieces()
{
    //SET WHITE PIECES:
    for(int row = 0; row < m_pieceRows; row++ ) {
        for(int col = 0; col < m_columns; col++) {
            QModelIndex index = m_model.index(row, col);
            QVariant playable = m_model.data(index, CheckersRoles::IsPlayableRole);
            if(playable.toBool()){
                CheckersModel::setPiece(index, Player::white);
            }
            else {
                Player player = Player::null;
                Type type = Type::null;
                QPair<Player, Type> piece(player, type);
                setData(index, QVariant::fromValue(piece), PieceRole);
            }
        }
    }

    //SET BLACK PIECES:
    for(int row = m_rows - 1; row >= m_rows - m_pieceRows; row--){
        for(int col = 0; col < m_columns; col++) {
            QModelIndex index = m_model.index(row, col);
            QVariant playable = m_model.data(index, CheckersRoles::IsPlayableRole);
            if(playable.toBool()){
                CheckersModel::setPiece(index, Player::black);
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

void CheckersModel::setPiece(QModelIndex index, Player player, Type type)
{
    Player playerToSet = player;
    Type typeToSet = type;

    QPair<Player, Type> piece(playerToSet, typeToSet);

    setData(index, QVariant::fromValue(piece), PieceRole);
}

void CheckersModel::setEmptyField(QModelIndex index)
{
    Player player = Player::null;
    Type type = Type::null;

    QPair<Player, Type> piece(player, type);

    setData(index, QVariant::fromValue(piece), PieceRole);
}

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
            }
            else {
                //qDebug() << "no piece";
                setData(index, QVariantList(), RangeRole);
            }
        }
    }
}

QList <QPair <char, int> > CheckersModel::getKingMoves(const QModelIndex &index, bool isWhite)
{
    QList <QPair <char, int> > possibleMoves {};

    //int rowNo = index.row();
    //int colNo = index.column();

    return possibleMoves;
}

QList <QPair <char, int> > CheckersModel::getManMoves(const QModelIndex &index, bool isWhite)
{
    QList <QPair <char, int> > possibleMoves {};

    int rowNo = index.row();
    int colNo = index.column();
    int direction = isWhite ? 1 : -1;

    if( (colNo != 0) && (colNo != (m_columns -1)) ) {
        QModelIndex checkindex1 = getIndex(rowNo + direction, colNo - 1);
        QModelIndex checkindex2 = getIndex(rowNo + direction, colNo + 1);
        if(!isPiecePresent(checkindex1)) {
            QVariant move = data(checkindex1, CoordinatesRole);
            possibleMoves.push_back(move.value<QPair<char, int>>());
        }
        if(!isPiecePresent(checkindex2)) {
            QVariant move = data(checkindex2, CoordinatesRole);
            possibleMoves.push_back(move.value<QPair<char, int>>());
        }
    }

    if( colNo == 0) {
        QModelIndex checkindex = getIndex(rowNo + direction, colNo + 1);
        if(!isPiecePresent(checkindex)) {
            QVariant move = data(checkindex, CoordinatesRole);
            possibleMoves.push_back(move.value<QPair<char, int>>());
        }
    }

    if( colNo == ( m_columns -1) ) {
        QModelIndex checkindex = getIndex(rowNo + direction, colNo - 1);
        if(!isPiecePresent(checkindex)) {
            QVariant move = data(checkindex, CoordinatesRole);
            possibleMoves.push_back(move.value<QPair<char, int>>());
        }
    }

    return possibleMoves;
}

