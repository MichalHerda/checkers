#ifndef CHECKERSMODEL_H
#define CHECKERSMODEL_H

#include <QObject>
#include <QStandardItemModel>

class CheckersModel : public QStandardItemModel
{
    Q_OBJECT
public:
    explicit CheckersModel(int rows = 8, int columns = 8);

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

    struct Piece {
        Player player;
        Type type;
    };

signals:

private:

};

#endif // CHECKERSMODEL_H
