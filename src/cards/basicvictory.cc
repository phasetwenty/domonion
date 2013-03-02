/*
 * BasicVictory.cpp
 *
 *  Created on: Oct 28, 2012
 *      Author: chris
 */

#include <string>

#include <card.h>
#include <cards/basicvictory.h>

BasicVictory::BasicVictory(std::string name,
    int cost,
    int initial_supply,
    std::string text) :
    Card(name, cost, initial_supply, text, kVictory) { }

BasicVictory::~BasicVictory() {
  // TODO Auto-generated destructor stub
}

void BasicVictory::Play(GameState& game) const {

}

bool BasicVictory::is_playable() const {
  return false;
}
