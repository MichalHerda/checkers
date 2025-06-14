#ifndef CHECKERSMODEL_H
#define CHECKERSMODEL_H

#include <QObject>
#include <QStandardItemModel>
#include <QMetaEnum>

struct CornersCoordinates {
    Q_GADGET

    Q_PROPERTY(QPointF topLeft MEMBER topLeft)
    Q_PROPERTY(QPointF topRight MEMBER topRight)
    Q_PROPERTY(QPointF bottomLeft MEMBER bottomLeft)
    Q_PROPERTY(QPointF bottomRight MEMBER bottomRight)

public:
    QPointF topLeft;
    QPointF topRight;
    QPointF bottomLeft;
    QPointF bottomRight;
};
Q_DECLARE_METATYPE(CornersCoordinates)

class CheckersModel : public QStandardItemModel
{
    Q_OBJECT

    friend class GameController;

public:
    enum CheckersRoles {
        FieldNameRole = Qt::UserRole + 1,
        IsPlayableRole,
        PieceRole,
        RangeRole,
        CaptureAvailableRole,
        MultiCaptureRole,
        IsSelectedRole,
        FieldCoordinatesRole,
        FieldCenterRole,
        PieceCoordinatesRole
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

    explicit CheckersModel();

    Q_INVOKABLE bool isPiecePresent(const QModelIndex &index);
    Q_INVOKABLE bool getPieceColor(const QModelIndex &index);
    Q_INVOKABLE bool getPieceType(const QModelIndex &index);

    Q_INVOKABLE int getColumnsNo();
    Q_INVOKABLE int getRowsNo();

    int getPieceRows();

    Q_INVOKABLE void resetModel();
    Q_INVOKABLE void printModel();

    Q_INVOKABLE bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    Q_INVOKABLE QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Q_INVOKABLE QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    Q_INVOKABLE QModelIndex getIndex(int row, int column);
    Q_INVOKABLE void setTurn();
    Q_INVOKABLE Player getTurn();
    Q_INVOKABLE QStandardItem* getItem(QModelIndex index);

    Q_INVOKABLE void selectField(QModelIndex index, bool selected = true);
    Q_INVOKABLE void deselectAllFields();

    Q_INVOKABLE void updateFieldsCoordinates(const QVariantList &fieldsCoordinates);
    Q_INVOKABLE void updatePiecesCoordinates(const QVariantList &fieldsCoordinates);
    Q_INVOKABLE void removePiece(QModelIndex from, QModelIndex to);

    Q_INVOKABLE QModelIndex getModelIndexFromGivenCoordinates(double averageX, double averageY);

    Q_INVOKABLE void setAllPiecesRange();
    Q_INVOKABLE bool isCaptureAvailable(const QModelIndex &index);

    Q_INVOKABLE void showScore();

    Q_PROPERTY (bool gameOn                    READ gameOnRead     WRITE gameOnWrite     NOTIFY gameOnChanged     )
    Q_PROPERTY (CheckersModel::Player player   READ playerRead     WRITE playerWrite     NOTIFY playerChanged     )

    bool gameOn = false;
    CheckersModel::Player player = CheckersModel::Player::null;

    bool gameOnRead()const;
    CheckersModel::Player playerRead()const;

    void gameOnWrite(bool gameOn);
    void playerWrite(CheckersModel::Player _player);

    QModelIndex findFieldIndexForPieceCenter(const QPointF &pieceCenter);
    Player getPlayerForCheck(const QModelIndex &index);

    bool isInsideBoard(int row, int col);
    QModelIndex indexFromPair(const QPair<char, int> &pos) const;
    bool canKingContinueCaptureFrom(int row, int col, QModelIndex initialKingIdx, QList<QModelIndex> &pathMoves, QList<QModelIndex> &checkedMoves);
    void initializePieces();

    void setPiece(QModelIndex index, Player player, Type type = Type::man); // function for initialization for board area with pieces
    void setEmptyField(QModelIndex index);                                  // <---as in the function name

signals:
    void gameOnChanged(bool _gameOn);
    void playerChanged(CheckersModel::Player _player);

private:
    int m_columns = 8;
    int m_rows = 8;
    int m_pieceRows = 3;

    int m_whiteScore = 0;
    int m_blackScore = 0;

    QStandardItemModel m_model;
    Player m_turn;

    void setColumns(int col);                                               // set custom board size
    void setRows(int row);
    void setPieceRows(int row);                                             // set custom rows number for piece (on game start)

    void setFieldsCoordinatesRole();
    void setFieldCenterRole();
    void setPiecesCoordinatesRole();

    QList <QPair <char, int> > getKingMoves(const QModelIndex &index, bool isWhite);
    QList <QPair <char, int> > getManMoves(const QModelIndex &index, bool isWhite);
    void reduceToBestKingCaptures(const QModelIndex &initialIdx, QList<QPair<char, int>> &captureMoves);

    QVector <CornersCoordinates> m_fieldsCoordinates;
    QVector <CornersCoordinates> m_piecesCoordinates;

    bool isOpponentAt(const QModelIndex &index, Player playerForCheck);
};

struct Piece {
    Q_GADGET

    Q_PROPERTY(CheckersModel::Player player MEMBER player)
    Q_PROPERTY(CheckersModel::Type type MEMBER type)

public:
    CheckersModel::Player player;
    CheckersModel::Type type;
};
Q_DECLARE_METATYPE(Piece)

QDebug operator<<(QDebug debug, const CornersCoordinates &coords);
QDebug operator<<(QDebug debug, const Piece &pieceRole);

#endif // CHECKERSMODEL_H
