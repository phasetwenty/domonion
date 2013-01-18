#include <vector>

#include <gamestate.h>
#include <playercollection.h>

GameState::GameState(std::vector<Player>& players) {
  players_ = new PlayerCollection(players);
}

const PlayerCollection* GameState::players() const {
  return players_;
}

GameState::~GameState() {
}

