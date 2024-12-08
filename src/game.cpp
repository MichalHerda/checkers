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

void Game::gameOnWrite(bool gameOn) {

}

void Game::playerWrite(CheckersModel::Player) {

}
