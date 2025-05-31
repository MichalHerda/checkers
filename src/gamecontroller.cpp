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
    //console.log("move valid")
    m_modelIndexToMove = s_model->getModelIndexFromGivenCoordinates(averageX, averageY);
    //console.log("model index: ", modelIndex)
    //console.log("model index to move: ", modelIndexToMove)

    //SWAP FIELDS VALUES:

    QVariant emptyPieceData = s_model->data(m_modelIndexToMove, CheckersModel::PieceRole);
                         //console.log("field to move before swap: ", emptyPieceData)
                         //console.log("field to move data color: ", emptyPieceData.player)
                         //console.log("field to move data type: ", emptyPieceData.type)

    QVariant pieceData = s_model->data(index, CheckersModel::PieceRole);
          //console.log("piece data: ", pieceData)
          //console.log("piece data color: ", pieceData.player)
          //console.log("piece data type: ", pieceData.type)

    bool isCapture = s_model->mustCapture(s_model->player);
    if(isCapture) {
        s_model->removePiece(index, m_modelIndexToMove);
    }

    s_model->setData(m_modelIndexToMove, pieceData, CheckersModel::PieceRole);
    s_model->setData(index, emptyPieceData, CheckersModel::PieceRole);
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
void GameController::changePlayer()
{
    bool isCapture = s_model -> mustCapture(s_model->player);

    if(!m_hasMultiCapture || !isCapture) {
        if(s_model->player == CheckersModel::Player::white) {
            s_model->player = CheckersModel::Player::black;
        }
        else {
            s_model->player = CheckersModel::Player::white;
        }
    }
}
//***************************************************************************************************************************************************************************************************************************************
