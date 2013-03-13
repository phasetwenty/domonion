/*
 * cardbank.cc
 *
 *  Created on: Mar 10, 2013
 *      Author: chris
 */
#include <algorithm>

#include <cards/base.h>
#include <cardbank.h>

namespace domonion {

CardBank::CardBank() : all_cards_(), selected_cards_() {
  InitializeAllCards();

  /*
   * TODO
   * This is a temporary construct.
   */
  for (std::vector<Card*>::const_iterator it = all_cards_.begin();
      it != all_cards_.end();
      ++it) {
    selected_cards_.push_back(*it);
  }
}

CardBank::~CardBank() { }

std::vector<Card*>* CardBank::Selection() const {
  std::vector<Card*>* result = new std::vector<Card*>;

  for (std::vector<Card*>::const_iterator it = selected_cards_.begin();
      it != selected_cards_.end();
      ++it) {
    result->push_back(*it);
  }

  return result;
}

void CardBank::InitializeAllCards() {
  /*
   * TODO
   * When cards are implemented, uncomment their initialization.
   */
//  all_cards_.push_back(cards::Adventurer());
//  all_cards_.push_back(cards::Bureaucrat());
//  all_cards_.push_back(cards::Cellar());
//  all_cards_.push_back(cards::Chancellor());
//  all_cards_.push_back(cards::Chapel());
  all_cards_.push_back(new cards::CouncilRoom());
//  all_cards_.push_back(cards::Feast());
  all_cards_.push_back(new cards::Festival());
//  all_cards_.push_back(cards::Gardens());
  all_cards_.push_back(new cards::Laboratory());
//  all_cards_.push_back(cards::Library());
  all_cards_.push_back(new cards::Market());
//  all_cards_.push_back(cards::Militia());
//  all_cards_.push_back(cards::Mine());
//  all_cards_.push_back(cards::Moat());
//  all_cards_.push_back(cards::Moneylender());
//  all_cards_.push_back(cards::Remodel());
  all_cards_.push_back(new cards::Smithy());
//  all_cards_.push_back(cards::Spy());
//  all_cards_.push_back(cards::Thief());
//  all_cards_.push_back(cards::ThroneRoom());
//  all_cards_.push_back(cards::Village());
//  all_cards_.push_back(cards::Witch());
  all_cards_.push_back(new cards::Woodcutter());
//  all_cards_.push_back(cards::Workshop());
}

} /* namespace domonion */
