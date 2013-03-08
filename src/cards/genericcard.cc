/*
 * genericcard.cc
 *
 *  Created on: Feb 27, 2013
 *      Author: chris
 */

#include <gamestate.h>
#include <cards/genericcard.h>

domonion::cards::GenericCard::GenericCard(std::string name,
  int cost,
  int initial_supply,
  std::string text,
  Types type) : Card(name, cost, initial_supply, text, 1, type) { }

domonion::cards::GenericCard::~GenericCard() {
  // TODO Auto-generated destructor stub
}

void domonion::cards::GenericCard::Play(domonion::GameState& game) const { }

bool domonion::cards::GenericCard::is_playable(const domonion::GameState& game) const {
  return true;
}
