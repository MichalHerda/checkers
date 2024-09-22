#ifndef CHECKERSMODEL_H
#define CHECKERSMODEL_H

#include <QObject>
#include <QStandardItemModel>

class CheckersModel : public QStandardItemModel
{
    Q_OBJECT

public:
    enum class CheckersRoles {
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
        king
    };
    Q_ENUM(Type)

    explicit CheckersModel(int rows = 8, int columns = 8);

    struct Piece {
        Player player;
        Type type;
    };

    Q_INVOKABLE void setTurn();
    Q_INVOKABLE Player getTurn();
signals:

private:
    Player m_turn;
};

#endif // CHECKERSMODEL_H
