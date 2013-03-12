/*
 * laboratory.h
 *
 *  Created on: Mar 8, 2013
 *      Author: chris
 */

#ifndef DOMONION_CARDS_BASE_H_
#define DOMONION_CARDS_BASE_H_

#include <card.h>

namespace domonion {
namespace cards {

/*
 * TODO
 * * Card selection from the hand
 * * Card reveal from the hand
 * * Card reveal from the draw pile
 */

class Adventurer : public Card {
public:
  Adventurer();
  virtual ~Adventurer();

  virtual void Play(GameState& game) const;

private:
  Adventurer(const Adventurer& other);
  Adventurer& operator=(const Adventurer& other);
};

class Laboratory : public Card {
public:
  Laboratory();
  virtual ~Laboratory();

  virtual void Play(GameState& game) const;

private:
  Laboratory(const Laboratory& other);
  Laboratory& operator=(const Laboratory& other);
};

} /* namespace cards */
} /* namespace domonion */
#endif /* DOMONION_CARDS_BASE_H_ */
