#include "gamelogic.h"
//***************************************************************************************************************************************************************************************************************************************
//GameLogic::GameLogic(QObject *parent)
//    : QObject{parent}
//{}
//***************************************************************************************************************************************************************************************************************************************
GameLogic::GameLogic(CheckersModel* model, int rows, int columns)
    : m_model(model), m_rows(rows), m_columns(columns)
{

}
//***************************************************************************************************************************************************************************************************************************************
bool GameLogic::mustCapture(CheckersModel::Player player)
{
    for(int row = 0, arrayIdx = 0; row < m_rows; row++) {
        for(int column = 0; column < m_columns; column++) {
            QModelIndex index = m_model->getIndex(row, column);
            bool isWhite =  m_model->getPieceColor(index);
            bool isCurrentPlayer = (player == CheckersModel::Player::white && isWhite) || (player == CheckersModel::Player::black && !isWhite);
            if(isCurrentPlayer) {
                bool captureAvailable =  m_model->isCaptureAvailable(index);
                if(captureAvailable) {
                    return true;
                }
            }
        }
    }
    return false;
}
//***************************************************************************************************************************************************************************************************************************************
