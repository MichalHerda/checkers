#ifndef CHECKERSMODEL_H
#define CHECKERSMODEL_H

#include <QObject>
#include <QStandardItemModel>

class CheckersModel : public QStandardItemModel
{
    Q_OBJECT

public:
    enum CheckersRoles {
        CoordinatesRole = Qt::UserRole + 1,
        IsPlayableRole,
        PieceRole,
        RangeRole,
        CaptureAvailableRole,
        MultiCaptureRole,
        IsSelectedRole
    };
    Q_ENUM(CheckersRoles)

    enum class Player {
        white,
        black
    };
    Q_ENUM(Player)

    enum class Type {
        man,
        king,
        null
    };
    Q_ENUM(Type)

    struct Piece {
        Player player;
        Type type;
    };

    explicit CheckersModel();

    Q_INVOKABLE void resetModel();
    Q_INVOKABLE void printModel();

    Q_INVOKABLE bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    Q_INVOKABLE QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Q_INVOKABLE QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    Q_INVOKABLE void setTurn();
    Q_INVOKABLE Player getTurn();
signals:

private:
    int m_columns = 8;
    int m_rows = 8;
    QStandardItemModel m_model;
    Player m_turn;

    void setColumns(int col);
    void setRows(int row);
};

#endif // CHECKERSMODEL_H
