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
Curse::Curse() : Card("Curse", 0, 40, ")-1(", 1, kCurse) { }

int Curse::points_provided(const GameState& game) const {
  return -1;
}

BasicTreasure::BasicTreasure(std::string name,
    int coin_provided,
    int cost,
    int initial_supply,
    std::string text) :
    Card(name, cost, initial_supply, text, 1, kTreasure),
    coin_provided_(coin_provided) { }

void BasicTreasure::Play(GameState& game) const {
  game.current_player().AddCoin(coin_provided(game));
}

int BasicTreasure::coin_provided(const GameState& game) const {
  return coin_provided_;
}

BasicVictory::BasicVictory(std::string name,
    int points_provided,
    int cost,
    int initial_supply,
    std::string text) :
    Card(name, cost, initial_supply, text, 1, kVictory),
    victory_points_(points_provided) { }

int BasicVictory::points_provided(const GameState& game) const {
  return victory_points_;
}

}
}
