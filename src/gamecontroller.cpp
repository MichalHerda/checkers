#include "gamecontroller.h"

//GameController::GameController(CheckersModel* model, QObject *parent)
//    : QObject{parent}
//{}
GameController::GameController(QObject *parent)
{

}

CheckersModel* GameController::s_model = nullptr;

bool GameController::isPlayersOwnPiece(const QModelIndex idx)
{
    return s_model->CheckersModel::getPieceColor(idx) && s_model->player == CheckersModel::Player::white ||
          !s_model->CheckersModel::getPieceColor(idx) && s_model->player == CheckersModel::Player::black;
}
