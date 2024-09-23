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

void CheckersModel::setTurn()
{
    m_turn == Player::black ? m_turn = Player::white : m_turn = Player::black;
}

CheckersModel::Player CheckersModel::getTurn()
{
    return m_turn;
}

