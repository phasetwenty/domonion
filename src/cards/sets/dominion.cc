/*
 * laboratory.cc
 *
 *  Created on: Mar 8, 2013
 *      Author: chris
 */

#include <cards/sets/dominion.h>
#include <gamestate.h>

/*
 * TODO
 * * Card selection from the hand
 * * Card reveal from the hand
 * * Card reveal from the draw pile
 */

namespace domonion {
namespace cards {

CouncilRoom::CouncilRoom() :
  Card("Council Room",
    5,
    GameState::kDefaultInitialSupply,
    "+4 Cards +1 Buy All other players draw a card.",
    1,
    kAction) {
}

CouncilRoom::~CouncilRoom() {
}

void CouncilRoom::Play(GameState& game) const {
  game.current_deck().Draw(4);
  game.current_player().AddBuys(1);

  for (std::vector<Player*>::const_iterator it = game.players().begin();
    it != game.players().end(); ++it) {
    if (*it == &game.current_player()) {
      continue;
    }

    (*it)->deck().Draw(1);
  }
}

Festival::Festival() : Card("Festival", 5, GameState::kDefaultInitialSupply, "+2 Actions +1 Buy +(2)", 1, kAction) { }

Festival::~Festival() { }

void Festival::Play(GameState& game) const {
  game.current_player().AddActions(2);
  game.current_player().AddBuys(1);
  game.current_player().AddCoin(2);
}

Laboratory::Laboratory() :
  Card("Laboratory",
    5,
    GameState::kDefaultInitialSupply,
    "+2 Cards +1 Action",
    1,
    Card::kAction) {
}

Laboratory::~Laboratory() {
}

void Laboratory::Play(GameState& game) const {
  game.current_player().deck().Draw(2);
  game.current_player().AddActions(1);
}

Market::Market() :
  Card("Market",
    5,
    GameState::kDefaultInitialSupply,
    "+1 Action +1 Card +1 Buy +(1)",
    1,
    Card::kAction) {
}

Market::~Market() {
}

void Market::Play(GameState& game) const {
  game.current_player().AddActions(1);
  game.current_deck().Draw(1);
  game.current_player().AddBuys(1);
  game.current_player().AddCoin(1);
}

Smithy::Smithy() :
  Card("Smithy",
    4,
    GameState::kDefaultInitialSupply,
    "+3 Cards",
    1,
    Card::kAction) {
}

Smithy::~Smithy() {
}

void Smithy::Play(GameState& game) const {
  game.current_deck().Draw(3);
}

Woodcutter::Woodcutter() :
  Card("Woodcutter",
    3,
    GameState::kDefaultInitialSupply,
    "+(2) +1 Buy",
    1,
    kAction) {
}

Woodcutter::~Woodcutter() { }

void Woodcutter::Play(GameState& game) const {
  game.current_player().AddCoin(2);
  game.current_player().AddBuys(1);
}

} /* namespace cards */
} /* namespace domonion */
