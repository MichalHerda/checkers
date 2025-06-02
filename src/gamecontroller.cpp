#include "gamecontroller.h"
//***************************************************************************************************************************************************************************************************************************************
GameController::GameController(CheckersModel* model, QObject *parent)
    : QObject{parent}, m_model(model)
{
    m_logic = std::make_unique<GameLogic>(model, model->getRowsNo(), model->getColumnsNo());
}
//***************************************************************************************************************************************************************************************************************************************
GameController::GameController(QObject *parent)
{

}
//***************************************************************************************************************************************************************************************************************************************
bool GameController::isPlayersOwnPiece(const QModelIndex idx)
{
    return m_model->CheckersModel::getPieceColor(idx) && m_model->player == CheckersModel::Player::white ||
          !m_model->CheckersModel::getPieceColor(idx) && m_model->player == CheckersModel::Player::black;
}
//***************************************************************************************************************************************************************************************************************************************
bool GameController::isMoveValid(QModelIndex index, double averageX, double averageY)
{
    qDebug() << "isMoveValid, index passed: " << index;
    QVariantList range = m_model -> data(index, CheckersModel::RangeRole).toList();
    qDebug() << "passed index range: "  << range;

    auto hasCapture = m_model -> data(index, CheckersModel::CaptureAvailableRole);
    if(!hasCapture.toBool() && m_model->mustCapture(m_model->player)) {
        return false;
    }

    QPointF pieceCenter(averageX, averageY);
    QModelIndex targetFieldIndex = m_model->findFieldIndexForPieceCenter(pieceCenter);
    qDebug() << "piece center is now inside field: " << targetFieldIndex;

    std::pair<char, int> targetCoordinate = m_model->data(targetFieldIndex, CheckersModel::FieldNameRole).value<std::pair<char, int>>();
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
    m_modelIndexToMove = m_model->getModelIndexFromGivenCoordinates(averageX, averageY);

    QVariant emptyPieceData = m_model->data(m_modelIndexToMove, CheckersModel::PieceRole);

    QVariant pieceData = m_model->data(index, CheckersModel::PieceRole);

    bool isCapture = m_model->mustCapture(m_model->player);

    if(isCapture) {
        m_model->removePiece(index, m_modelIndexToMove);
    }

    m_model->setData(m_modelIndexToMove, pieceData, CheckersModel::PieceRole);
    m_model->setData(index, emptyPieceData, CheckersModel::PieceRole);

    m_model->setAllPiecesRange();
}
//***************************************************************************************************************************************************************************************************************************************
void GameController::evaluatePromotionToKing(QModelIndex index,double averageX, double averageY)
{
    QModelIndex modelIndexToMove = m_model->getModelIndexFromGivenCoordinates(averageX, averageY);
    bool hasMultiCapture = m_model->isCaptureAvailable(m_modelIndexToMove);

    if(!m_hasMultiCapture) {
        if(m_model->player == CheckersModel::Player::white &&
            m_model->getPieceType(index) == false &&
            modelIndexToMove.row() == 0) {
            qDebug() << "promote to king";
            m_model->setEmptyField(modelIndexToMove);
            m_model->setPiece(modelIndexToMove, m_model->player, CheckersModel::Type::king);
        }

        if(m_model->player == CheckersModel::Player::black &&
            m_model->getPieceType(index) == false &&
            modelIndexToMove.row() == 7) {
            qDebug() << "promote to king";
            m_model->setEmptyField(modelIndexToMove);
            m_model->setPiece(modelIndexToMove, m_model->player, CheckersModel::Type::king);
        }
    }
}
//***************************************************************************************************************************************************************************************************************************************
void GameController::changePlayer(double averageX, double averageY, bool mustCapture)
{
    qDebug() << "CHANGE PLAYER: ";
    qDebug() << "   player: " << m_model->player;
    QModelIndex indexToMove = m_model->getModelIndexFromGivenCoordinates(averageX, averageY);
    qDebug() << "   indexToMove: " << indexToMove;
    qDebug() << "   isCapture: " << mustCapture;
    bool hasMultiCapture = m_model->isCaptureAvailable(indexToMove);
    qDebug() << "   hasMultiCapture: " << hasMultiCapture;

    if(!hasMultiCapture || !mustCapture) {
        if(m_model->player == CheckersModel::Player::white) {
            m_model->player = CheckersModel::Player::black;
            emit m_model->playerChanged(CheckersModel::Player::black);
        }
        else {
            m_model->player = CheckersModel::Player::white;
            emit m_model->playerChanged(CheckersModel::Player::white);
        }
    }
}
//***************************************************************************************************************************************************************************************************************************************
bool GameController::mustCapture(CheckersModel::Player player)
{
    if(m_logic) {
        return m_logic -> mustCapture(player);
    }
    else {
        qDebug() << "m_logic is nullptr!";
        return false;
    }
}
//***************************************************************************************************************************************************************************************************************************************
