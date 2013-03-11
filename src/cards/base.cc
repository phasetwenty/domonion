/*
 * laboratory.cc
 *
 *  Created on: Mar 8, 2013
 *      Author: chris
 */

#include <gamestate.h>
#include <cards/laboratory.h>

namespace domonion {
namespace cards {

Laboratory::Laboratory() :
  Card(std::string("Laboratory"),
    5,
    GameState::kDefaultInitialSupply,
    std::string("+2 Cards\n+1 Action"),
    1,
    Card::kAction) {
}

Laboratory::~Laboratory() {
  // TODO Auto-generated destructor stub
}

void Laboratory::Play(GameState& game) const {
  game.current_player().deck().Draw(2);
  game.current_player().AddActions(1);
}

} /* namespace cards */
} /* namespace domonion */
