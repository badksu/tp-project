#include <iostream>

#include "player.h"

class Game {
  std::vector<Player> players;

  void initPlayers();
  int getWinner();

   public:
  void play();
};