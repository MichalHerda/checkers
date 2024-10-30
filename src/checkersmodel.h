#ifndef CHECKERSMODEL_H
#define CHECKERSMODEL_H

#include <QObject>
#include <QStandardItemModel>
#include <QMetaEnum>

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
        black,
        null
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

    Q_INVOKABLE bool isPiecePresent(const QModelIndex &index);
    Q_INVOKABLE bool getPieceColor(const QModelIndex &index);
    Q_INVOKABLE bool getPieceType(const QModelIndex &index);

    Q_INVOKABLE int getColumnsNo();
    Q_INVOKABLE int getRowsNo();

    Q_INVOKABLE void resetModel();
    Q_INVOKABLE void printModel();

//    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    Q_INVOKABLE QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Q_INVOKABLE QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    Q_INVOKABLE QModelIndex getIndex(int row, int column);
    Q_INVOKABLE void setTurn();
    Q_INVOKABLE Player getTurn();
    Q_INVOKABLE QStandardItem* getItem(QModelIndex index);

    Q_INVOKABLE void deselectAllFields();
    Q_INVOKABLE void selectField(QModelIndex idx, bool selected = true);

signals:

private:
    int m_columns = 8;
    int m_rows = 8;
    int m_pieceRows = 3;

//    QMetaEnum m_rolesMetaEnum;
//    QHash<int, QByteArray> m_rolesMap;

    QStandardItemModel m_model;
    Player m_turn;

    void setColumns(int col);                                             // set custom board size
    void setRows(int row);
    void setPieceRows(int row);                                           // set custom rows number for piece (on game start)

    void initializePieces();
    void setPiece(QModelIndex idx, Player player, Type type = Type::man); // function for initialization for board area with pieces
    void setEmptyField(QModelIndex idx);                                  // <---as in the function name

    void setAllPiecesRange();
    QList <QPair <char, int> > getKingMoves(const QModelIndex &index, bool isWhite);
    QList <QPair <char, int> > getManMoves(const QModelIndex &index, bool isWhite);
};

#endif // CHECKERSMODEL_H
