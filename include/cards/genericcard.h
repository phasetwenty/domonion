/*
 * genericcard.h
 *
 *  Created on: Feb 27, 2013
 *      Author: chris
 */

#ifndef DOMONION_GENERICCARD_H_
#define DOMONION_GENERICCARD_H_

#include <card.h>

class GameState;

/*
 * Generic card useful for testing. Only supports a single type attached to it.
 */
class GenericCard: public Card {
public:
  GenericCard(std::string name,
    int cost,
    int initial_supply,
    std::string text,
    Types type);
  virtual ~GenericCard();

  virtual void Play(GameState& game) const;

  virtual bool is_playable(const GameState& game) const;
};

#endif /* DOMONION_GENERICCARD_H_ */
