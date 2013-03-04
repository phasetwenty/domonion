/*
 * genericcard.cc
 *
 *  Created on: Feb 27, 2013
 *      Author: chris
 */

#include <gamestate.h>
#include <cards/genericcard.h>

GenericCard::GenericCard(std::string name,
  int cost,
  int initial_supply,
  std::string text,
  Types type) : Card(name, cost, initial_supply, text, 1, type) { }

GenericCard::~GenericCard() {
  // TODO Auto-generated destructor stub
}

void GenericCard::Play(GameState& game) const { }

bool GenericCard::is_playable(const GameState& game) const {
  return true;
}
