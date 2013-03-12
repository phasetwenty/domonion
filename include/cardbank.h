/*
 * cardbank.h
 *
 *  Created on: Mar 10, 2013
 *      Author: chris
 */

#ifndef domonion_domonion_CARDBANK_H_
#define domonion_domonion_CARDBANK_H_

#include <cards/base.h>
#include <card.h>

class std::vector<Card*>;

namespace domonion {

class CardBank {
public:
  CardBank();
  CardBank(std::vector<Card*> initial);
  virtual ~CardBank();


private:
  std::vector<Card> all_cards_;

  CardBank(const CardBank& other) {}


};

} /* namespace domonion */
#endif /* CARDBANK_H_ */
