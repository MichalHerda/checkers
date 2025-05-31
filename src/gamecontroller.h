#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include "checkersmodel.h"

class GameController : public QObject
{
    Q_OBJECT
public:
    explicit GameController(CheckersModel* model, QObject *parent = nullptr);

signals:

private:
    CheckersModel* m_model;
};

#endif // GAMECONTROLLER_H
