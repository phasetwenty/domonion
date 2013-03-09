/*
 * BasicVictory.cpp
 *
 *  Created on: Oct 28, 2012
 *      Author: chris
 */

#include <string>

#include <card.h>
#include <cards/basicvictory.h>

namespace domonion {
namespace cards {

BasicVictory::BasicVictory(std::string name,
    int points_provided,
    int cost,
    int initial_supply,
    std::string text) :
    Card(name, cost, initial_supply, text, 1, kVictory),
    victory_points_(points_provided) { }

BasicVictory::~BasicVictory() {
  // TODO Auto-generated destructor stub
}

void BasicVictory::Play(domonion::GameState& game) const {

}

int BasicVictory::points_provided() const {
  return victory_points_;
}

}
}

