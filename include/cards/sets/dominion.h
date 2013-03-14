/*
 * laboratory.h
 *
 *  Created on: Mar 8, 2013
 *      Author: chris
 */

#ifndef DOMONION_CARDS_DOMINION_H_
#define DOMONION_CARDS_DOMINION_H_

#include <cards/base.h>
#include <card.h>

#define CARD_CLASS_DECL(name) \
  class name : public Card {\
  public:\
    name();\
    virtual ~name() { }\
    \
    virtual void Play(GameState& game) const;\
  private:\
    name(const name& other);\
    name& operator=(const name& other);\
  };

namespace domonion {
namespace cards {

CARD_CLASS_DECL(Adventurer)
CARD_CLASS_DECL(Bureaucrat)
CARD_CLASS_DECL(Cellar)
CARD_CLASS_DECL(Chancellor)
CARD_CLASS_DECL(Chapel)

class CouncilRoom : public Card {
public:
  CouncilRoom();
  virtual ~CouncilRoom() { }

  virtual void Play(GameState& game) const;
  virtual std::string* ToString() const;
private:
  CouncilRoom(const CouncilRoom& other);
  CouncilRoom& operator=(const CouncilRoom& other);
};

CARD_CLASS_DECL(Feast)
CARD_CLASS_DECL(Festival)

class Gardens : public Card, public IPointsProvider {
public:
  Gardens();
  ~Gardens() { }

  virtual void Play(GameState& game) const { }

  virtual int initial_supply(int player_count) const;
  virtual int points_provided(const GameState& game) const;
};

CARD_CLASS_DECL(Laboratory)
CARD_CLASS_DECL(Library)
CARD_CLASS_DECL(Market)
CARD_CLASS_DECL(Militia)
CARD_CLASS_DECL(Mine)
CARD_CLASS_DECL(Moat)
CARD_CLASS_DECL(Moneylender)
CARD_CLASS_DECL(Remodel)
CARD_CLASS_DECL(Smithy)
CARD_CLASS_DECL(Spy)
CARD_CLASS_DECL(Thief)
CARD_CLASS_DECL(ThroneRoom)
CARD_CLASS_DECL(Village)
CARD_CLASS_DECL(Witch)
CARD_CLASS_DECL(Woodcutter)
CARD_CLASS_DECL(Workshop)

} /* namespace cards */
} /* namespace domonion */
#endif /* DOMONION_CARDS_DOMINION_H_ */
