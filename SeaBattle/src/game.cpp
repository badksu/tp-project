#include "game.h"

#include <iostream>

void Game::initPlayers() {
  for (size_t playerNum = 1; playerNum <= 2; ++playerNum) {
    Player newPlayer;
    newPlayer.initSelf(playerNum);
    players.push_back(newPlayer);
  }
  for (size_t i = 0; i < 2; ++i) {
    players[i].setOpponentsField(players[i ^ 1].getOwnField());
  }
}

int Game::getWinner() {
  int result = -1;
  for (size_t i = 0; i < 2; ++i) {
    result = (players[i].getAliveShips() > 0 ? -1 : 1 - i);
  }
  return result;
}

void Game::play() {
  initPlayers();

  int whoIsMoving = 0;
  int winner = -1;

  while ((winner = getWinner()) == -1) {
    whoIsMoving ^= (players[whoIsMoving].makeMove() ? 0 : 1);
  }
  std::cout << "Player " << players[winner].getName() << " win" << std::endl;
}