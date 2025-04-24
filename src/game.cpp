#include "game.h"

Game::Game(QObject *parent)
    : QObject{parent}
{}

bool Game::gameOnRead()const {
    return gameOn;
}

CheckersModel::Player Game::playerRead()const {
    return player;
}

void Game::gameOnWrite(bool _gameOn) {
    gameOn = _gameOn;
    emit gameOnChanged(_gameOn);
}

void Game::playerWrite(CheckersModel::Player _player) {
    player = _player;
    emit playerChanged(_player);
}
