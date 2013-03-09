/*
 * laboratory.h
 *
 *  Created on: Mar 8, 2013
 *      Author: chris
 */

#ifndef DOMONION_CARDS_LABORATORY_H_
#define DOMONION_CARDS_LABORATORY_H_

#include <card.h>

namespace domonion {
namespace cards {

class Laboratory: public Card {
public:
  Laboratory();
  virtual ~Laboratory();

  virtual void Play(GameState& game) const;
};

} /* namespace cards */
} /* namespace domonion */
#endif /* DOMONION_CARDS_LABORATORY_H_ */
