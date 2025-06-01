#include "gamecontroller.h"
//***************************************************************************************************************************************************************************************************************************************
//GameController::GameController(CheckersModel* model, QObject *parent)
//    : QObject{parent}
//{}
GameController::GameController(QObject *parent)
{

}
//***************************************************************************************************************************************************************************************************************************************
CheckersModel* GameController::s_model = nullptr;

bool GameController::isPlayersOwnPiece(const QModelIndex idx)
{
    return s_model->CheckersModel::getPieceColor(idx) && s_model->player == CheckersModel::Player::white ||
          !s_model->CheckersModel::getPieceColor(idx) && s_model->player == CheckersModel::Player::black;
}
//***************************************************************************************************************************************************************************************************************************************
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
//***************************************************************************************************************************************************************************************************************************************
void GameController::executeMove(QModelIndex index, double averageX, double averageY)
{
    m_modelIndexToMove = s_model->getModelIndexFromGivenCoordinates(averageX, averageY);

    QVariant emptyPieceData = s_model->data(m_modelIndexToMove, CheckersModel::PieceRole);

    QVariant pieceData = s_model->data(index, CheckersModel::PieceRole);

    bool isCapture = s_model->mustCapture(s_model->player);

    if(isCapture) {
        s_model->removePiece(index, m_modelIndexToMove);
    }

    s_model->setData(m_modelIndexToMove, pieceData, CheckersModel::PieceRole);
    s_model->setData(index, emptyPieceData, CheckersModel::PieceRole);

    //m_hasMultiCapture = s_model->isCaptureAvailable(m_modelIndexToMove);
    s_model->setAllPiecesRange();
}
//***************************************************************************************************************************************************************************************************************************************
void GameController::evaluatePromotionToKing(QModelIndex index,double averageX, double averageY)
{
    m_modelIndexToMove = s_model->getModelIndexFromGivenCoordinates(averageX, averageY);
    m_hasMultiCapture = s_model->isCaptureAvailable(m_modelIndexToMove);

    if(!m_hasMultiCapture) {
        //checkersModelInstance.evaluatePromotionToKing(m_modelIndexToMove)
        if(s_model->player == CheckersModel::Player::white &&
            s_model->getPieceType(index) == false &&
            index.row() == 0) {
            qDebug() << "promote to king";
            s_model->setEmptyField(index);
            s_model->setPiece(index, s_model->player, CheckersModel::Type::king);
        }

        if(s_model->player == CheckersModel::Player::black &&
            s_model->getPieceType(index) == false &&
            index.row() == 7) {
            qDebug() << "promote to king";
            s_model->setEmptyField(index);
            s_model->setPiece(index, s_model->player, CheckersModel::Type::king);
        }
    }
}
//***************************************************************************************************************************************************************************************************************************************
void GameController::changePlayer(double averageX, double averageY, bool mustCapture)
{
    qDebug() << "CHANGE PLAYER: ";
    qDebug() << "   player: " << s_model->player;
    QModelIndex indexToMove = s_model->getModelIndexFromGivenCoordinates(averageX, averageY);
    qDebug() << "   indexToMove: " << indexToMove;
    //bool isCapture = s_model -> mustCapture(s_model->player);
    qDebug() << "   isCapture: " << mustCapture;
    bool hasMultiCapture = s_model->isCaptureAvailable(indexToMove);
    qDebug() << "   hasMultiCapture: " << hasMultiCapture;

    if(!hasMultiCapture || !mustCapture) {
        if(s_model->player == CheckersModel::Player::white) {
            s_model->player = CheckersModel::Player::black;
        }
        else {
            s_model->player = CheckersModel::Player::white;
        }
    }
}
//***************************************************************************************************************************************************************************************************************************************
bool GameController::mustCapture(CheckersModel::Player player)
{
    return s_model -> mustCapture(player);
}
//***************************************************************************************************************************************************************************************************************************************
