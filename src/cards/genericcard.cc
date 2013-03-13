/*
 * genericcard.cc
 *
 *  Created on: Feb 27, 2013
 *      Author: chris
 */

#include <gamestate.h>
#include <cards/genericcard.h>

namespace domonion {
namespace cards {

GenericCard::GenericCard(std::string name,
  int cost,
  std::string text,
  Types type) : Card(name, cost, text, 1, type) { }

GenericCard::~GenericCard() {
  // TODO Auto-generated destructor stub
}

void GenericCard::Play(GameState& game) const { }

}
}
