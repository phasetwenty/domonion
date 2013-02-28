/*
 * basictreasure.cc
 *
 *  Created on: Oct 10, 2012
 *      Author: chris
 */

#include <gamestate.h>
#include <cards/basictreasure.h>

BasicTreasure::BasicTreasure(std::string name,
    int coin_provided,
    int cost,
    int initial_supply,
    std::string text) :
    Card(name, cost, initial_supply, text, "Treasure"),
    coin_provided_(coin_provided) {}

BasicTreasure::~BasicTreasure() {

}

void BasicTreasure::Play(GameState& game) const {
  game.current_player().AddCoin(coin_provided());
}

int BasicTreasure::coin_provided() const {
  return coin_provided_;
}

bool BasicTreasure::is_playable() const {
  return true;
}
