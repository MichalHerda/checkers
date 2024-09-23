#include "checkersmodel.h"

CheckersModel::CheckersModel()
{

}

void CheckersModel::resetModel(int columns, int rows)
{
    this->CheckersModel::setRowCount(rows);
    this->CheckersModel::setColumnCount(columns);

    for(char col = 0 ; col < columns; col++) {
        char column = 'A' + col;
        for(int row = 1; row <= rows; row++) {
            qDebug() << "column: " << column << ", row: " << row;
            QModelIndex indexToGet = index(row, col);
            QPair<char, int> coordinates(column, row);
            setData(indexToGet, QVariant::fromValue(coordinates), CoordinatesRole);
        }
    }
}

bool CheckersModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    switch(role) {
        case CheckersRoles::CoordinatesRole: {
            qDebug() << "CoordinateRole:" << value;
            break;
        }
        case CheckersRoles::IsPlayableRole: {
            qDebug() << "IsPlayableRole";
            break;
        }
        case CheckersRoles::PieceRole: {
            qDebug() << "PieceRole";
            break;
        }
        case CheckersRoles::RangeRole: {
            qDebug() << "RangeRole";
            break;
        }
        case CheckersRoles::CaptureAvailableRole: {
            qDebug() << "CaptureAvailableRole";
            break;
        }
        case CheckersRoles::MultiCaptureRole: {
            qDebug() << "MultiCaptureRole";
            break;
        }
        case CheckersRoles::IsSelectedRole: {
            qDebug() << "IsSelectedRole";
            break;
        }
        default: {
            qDebug() << "Default Role";
            break;
        }
    }
    return true;
}

QVariant CheckersModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        qDebug() << "function CheckersModel::data: index is not valid";
    }

    switch(role) {
        case CheckersRoles::CoordinatesRole: {
            return QVariant::fromValue(QPair<char, int>('A' + index.column(), index.row() + 1));
        }
        case CheckersRoles::IsPlayableRole: {
            return QVariant();
        }
        case CheckersRoles::PieceRole: {
            return QVariant();
        }
        case CheckersRoles::RangeRole: {
            return QVariant();
        }
        case CheckersRoles::CaptureAvailableRole: {
            return QVariant();
        }
        case CheckersRoles::MultiCaptureRole: {
            return QVariant();
        }
        case CheckersRoles::IsSelectedRole: {
            return QVariant();
        }
        default: {
             return QVariant();
        }
    }
    return QVariant();
}

QModelIndex CheckersModel::index(int row, int column, const QModelIndex &parent) const
{
    if(!CheckersModel::hasIndex(row, column)) {
        qDebug() << "index is not valid";
        return QModelIndex();
    }
    else {
        qDebug() << "index is valid";
        return CheckersModel::createIndex(row, column);
    }
}

void CheckersModel::printModel() {
    int rowCount = this->rowCount();
    int columnCount = this->columnCount();

    for (int col = 0; col < columnCount; col++) {
        char column = 'A' + col;
        for (int row = 0; row < rowCount; row++) {
            QModelIndex index = this->index(row, col);
            QVariant data = this->data(index, CheckersRoles::CoordinatesRole); // Użyj odpowiedniej roli
            qDebug() << "Column: " << column << ", Row: " << row + 1 << ", Data:" << data;
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

