/*
 * laboratory.cc
 *
 *  Created on: Mar 8, 2013
 *      Author: chris
 */

#include <cardbank.h>
#include <cards/sets/dominion.h>
#include <gamestate.h>
#include <supplypile.h>

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
    "+4 Cards +1 Buy All other players draw a card.",
    1,
    kAction) {
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

Festival::Festival() :
  Card("Festival", 5, "+2 Actions +1 Buy +(2)", 1, kAction) {
}

void Festival::Play(GameState& game) const {
  game.current_player().AddActions(2);
  game.current_player().AddBuys(1);
  game.current_player().AddCoin(2);
}

Gardens::Gardens() :
  Card("Gardens", 4, "Worth )1( for every 10 cards in your deck.", 1, kVictory) {
}

int Gardens::initial_supply(int player_count) const {
  return player_count < 3 ? 8 : 12;
}

int Gardens::points_provided(const GameState& game) const {
  /*
   * There is a subtlety when running the Gardens victory point counter.
   * Cards don't know which deck they're in, so Gardens needs more information.
   * A workaround is to simply rely on the current player being set correctly.
   */
  return game.current_deck().size() % 10;
}

Laboratory::Laboratory() :
  Card("Laboratory", 5, "+2 Cards +1 Action", 1, Card::kAction) {
}

void Laboratory::Play(GameState& game) const {
  game.current_player().deck().Draw(2);
  game.current_player().AddActions(1);
}

Market::Market() :
  Card("Market", 5, "+1 Action +1 Card +1 Buy +(1)", 1, Card::kAction) {
}

void Market::Play(GameState& game) const {
  game.current_player().AddActions(1);
  game.current_deck().Draw(1);
  game.current_player().AddBuys(1);
  game.current_player().AddCoin(1);
}

Smithy::Smithy() :
  Card("Smithy", 4, "+3 Cards", 1, Card::kAction) {
}

void Smithy::Play(GameState& game) const {
  game.current_deck().Draw(3);
}

Village::Village() :
  Card("Village", 3, "+1 Card +2 Actions", 1, kAction) {
}

void Village::Play(GameState& game) const {
  game.current_deck().Draw(1);
  game.current_player().AddActions(2);
}

Witch::Witch() :
  Card("Witch",
    5,
    "+2 Cards Each other player gains a curse",
    2,
    Card::kAction,
    Card::kAttack) {
}

void Witch::Play(GameState& game) const {
  game.current_deck().Draw(2);

  SupplyPile *curse_pile = game.FindSupplyPile("Curse");
  for (std::vector<Player*>::const_iterator it = game.players().begin();
    it != game.players().end(); ++it) {
    if (*it == &game.current_player()) {
      continue;
    }

    bool result = curse_pile->BuyOrGain();
    if (result) {
      (*it)->deck().Gain(curse_pile->card());
    }
  }
}

Woodcutter::Woodcutter() :
  Card("Woodcutter", 3, "+(2) +1 Buy", 1, kAction) {
}

void Woodcutter::Play(GameState& game) const {
  game.current_player().AddCoin(2);
  game.current_player().AddBuys(1);
}

} /* namespace cards */
} /* namespace domonion */
