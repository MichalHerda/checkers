#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include "checkersmodel.h"

class GameController : public QObject
{
    Q_OBJECT
public:
    //explicit GameController(CheckersModel* model, QObject *parent = nullptr);
    explicit GameController(QObject *parent = nullptr);

    static CheckersModel *s_model;

    Q_INVOKABLE bool isPlayersOwnPiece(const QModelIndex idx);
    Q_INVOKABLE bool isMoveValid(QModelIndex index, double averageX, double averageY);
signals:

private:
    CheckersModel* m_model;
};

#endif // GAMECONTROLLER_H
