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

bool GameController::isMoveValid(QModelIndex index, double averageX, double averageY)
{
    //return s_model->CheckersModel::isMoveValid(index, averageX, averageY);
    qDebug() << "isMoveValid, index passed: " << index;
    QVariantList range = s_model -> data(index, CheckersModel::RangeRole).toList();
    qDebug() << "passed index range: "  << range;

    auto hasCapture = s_model -> data(index, CheckersModel::CaptureAvailableRole);
    if(!hasCapture.toBool() && s_model->mustCapture(s_model->player)) {
        return false;
    }

    QPointF pieceCenter(averageX, averageY);
    QModelIndex targetFieldIndex = s_model->findFieldIndexForPieceCenter(pieceCenter);
    qDebug() << "piece center is now inside field: " << targetFieldIndex;

    std::pair<char, int> targetCoordinate = s_model->data(targetFieldIndex, CheckersModel::FieldNameRole).value<std::pair<char, int>>();
    qDebug() << "target coordinate: " << targetCoordinate;
    for (const QVariant &item : range) {
        std::pair<char, int> rangeCoordinate = item.value<std::pair<char, int>>();
        if (rangeCoordinate == targetCoordinate) {
            qDebug() << "Pole docelowe znajduje się w zakresie ruchu pionka.";
            return true;
        }
    }

    qDebug() << "Pole docelowe nie znajduje się w zakresie pionka";
    return false;
}
