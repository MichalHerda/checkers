#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <QObject>
#include "checkersmodel.h"

class GameLogic : public QObject
{
    Q_OBJECT
public:
    //explicit GameLogic(QObject *parent = nullptr);
    explicit GameLogic(int rows, int columns);

signals:

private:
    int m_rows;
    int m_columns;
};

#endif // GAMELOGIC_H
