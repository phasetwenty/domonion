/*
 * cardbank.h
 *
 *  Created on: Mar 10, 2013
 *      Author: chris
 */

#ifndef domonion_domonion_CARDBANK_H_
#define domonion_domonion_CARDBANK_H_

#include <cards/base.h>

class Card;
class std::vector<Card>;

namespace domonion {

class CardBank {
public:
  CardBank();
  virtual ~CardBank();

private:
  std::vector<Card> cards_;

  CardBank(const CardBank& other) {}


};

} /* namespace domonion */
#endif /* CARDBANK_H_ */
