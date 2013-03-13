/*
 * base.cc
 *
 *  Created on: Mar 13, 2013
 *      Author: chris
 */

#include <cards/base.h>
#include <gamestate.h>

namespace domonion {
namespace cards {
Curse::Curse() :
  Card("Curse", 0, ")-1(", 1, kCurse) {
}

int Curse::initial_supply(int player_count) const {
  int result = 0;
  if (player_count < 3) {
    result = 10;
  } else if (player_count == 3) {
    result = 20;
  } else if (player_count > 3) {
    result = 30;
  }
  return result;
}

int Curse::points_provided(const GameState& game) const {
  return -1;
}

BasicTreasure::BasicTreasure(std::string name,
  int coin_provided,
  int cost,
  int initial_supply,
  std::string text) :
  Card(name, cost, text, 1, kTreasure), coin_provided_(coin_provided), initial_supply_(initial_supply) {
}

void BasicTreasure::Play(GameState& game) const {
  game.current_player().AddCoin(coin_provided(game));
}

int BasicTreasure::coin_provided(const GameState& game) const {
  return coin_provided_;
}

int BasicTreasure::initial_supply(int player_count) const {
  return initial_supply_;
}

BasicVictory::BasicVictory(std::string name,
  int points_provided,
  int cost,
  int initial_supply,
  std::string text) :
  Card(name, cost, text, 1, kVictory), initial_supply_(initial_supply), victory_points_(points_provided) {
}

int BasicVictory::initial_supply(int player_count) const {
  return initial_supply_;
}

int BasicVictory::points_provided(const GameState& game) const {
  return victory_points_;
}

}
}
