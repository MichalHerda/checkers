#include "checkersmodel.h"

CheckersModel::CheckersModel()
{

}

void CheckersModel::resetModel()
{
    m_model.setRowCount(m_rows);
    m_model.setColumnCount(m_columns);

    for(int col = 0 ; col < m_columns; col++) {
        char column = 'A' + col;
        for(int row = 0; row < m_rows; row++) {
            qDebug() << "column: " << column << "row: " << row + 1;

            QStandardItem* item = new QStandardItem();
            qDebug()<<"item (resetModel): " << item;
            m_model.setItem(row, col, item);

            QModelIndex indexToGet = m_model.index(row, col);
            qDebug() << "index got: " << indexToGet;
            QPair<char, int> coordinates(column, row + 1);
            bool playable = (col + row) % 2 == 0;
            setData(indexToGet, QVariant::fromValue(coordinates), CoordinatesRole);
            setData(indexToGet, QVariant::fromValue(playable), IsPlayableRole);
        }
    }
}

bool CheckersModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid()) {
        qDebug() << "setData() !index.isValid()";
        return false;
    }

    qDebug() << "index: " << index;
    QStandardItem *item = m_model.itemFromIndex(index);

    if (!item) {
        qDebug() << "!item";
        return false;
    }

    switch(role) {
        case CheckersRoles::CoordinatesRole: {
            qDebug() << "CoordinateRole:" << value;
            item->setData(value, CoordinatesRole);
            break;
        }
        case CheckersRoles::IsPlayableRole: {
            qDebug() << "IsPlayableRole" << value;
            item->setData(value, IsPlayableRole);
            break;
        }
        case CheckersRoles::PieceRole: {
            qDebug() << "PieceRole";
            item->setData(value, PieceRole);
            break;
        }
        case CheckersRoles::RangeRole: {
            qDebug() << "RangeRole";
            item->setData(value, RangeRole);
            break;
        }
        case CheckersRoles::CaptureAvailableRole: {
            qDebug() << "CaptureAvailableRole";
            item->setData(value, CaptureAvailableRole);
            break;
        }
        case CheckersRoles::MultiCaptureRole: {
            qDebug() << "MultiCaptureRole";
            item->setData(value, MultiCaptureRole);
            break;
        }
        case CheckersRoles::IsSelectedRole: {
            qDebug() << "IsSelectedRole";
            item->setData(value, IsSelectedRole);
            break;
        }
        default: {
            qDebug() << "Default Role";
            break;
        }
    }
    emit dataChanged(index, index, {role});
    return true;
}

QVariant CheckersModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        qDebug() << "function CheckersModel::data: index is not valid";
        return QVariant();
    }

    const QStandardItem *item = itemFromIndex(index);

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
        qDebug() << "index is not valid";
        return QModelIndex();
    }
    else {
        qDebug() << "index is valid";
        return CheckersModel::createIndex(row, column);
    }
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
            qDebug() << "Column: " << column << ", Row: " << row + 1 << ", Coordinate: " << coordinate << ", Playable: " << playable;
        }
    }
}

void CheckersModel::setTurn()
{
    m_turn == Player::black ? m_turn = Player::white : m_turn = Player::black;
}

CheckersModel::Player CheckersModel::getTurn()
{
    return m_turn;
}

void CheckersModel::setColumns(int col)
{
    if(col % 2 != 0) {
        qDebug() << "the number of columns must be even. Added col + 1";
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
        qDebug() << "the number of rows must be even. Added row + 1";
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
        qDebug() << "to many piece rows. Setting to maximum allowed: " << maxPieceRows;
        m_pieceRows = maxPieceRows;
    }
    else {
        qDebug() << "set " << row << " pieces rows";
        m_pieceRows = row;
    }
}

void CheckersModel::initializePieces()
{
    //for(int i = )
}
