/*
 * BasicVictory.cpp
 *
 *  Created on: Oct 28, 2012
 *      Author: chris
 */

#include <string>

#include <card.h>
#include <cards/basicvictory.h>

domonion::cards::BasicVictory::BasicVictory(std::string name,
    int points_provided,
    int cost,
    int initial_supply,
    std::string text) :
    Card(name, cost, initial_supply, text, 1, kVictory),
    victory_points_(points_provided) { }

domonion::cards::BasicVictory::~BasicVictory() {
  // TODO Auto-generated destructor stub
}

void domonion::cards::BasicVictory::Play(domonion::GameState& game) const {

}

bool domonion::cards::BasicVictory::is_playable() const {
  return false;
}

int domonion::cards::BasicVictory::points_provided() const {
  return victory_points_;
}
