/*
 * cardbank.h
 *
 *  Created on: Mar 10, 2013
 *      Author: chris
 */

#ifndef DOMONION_CARDBANK_H_
#define DOMONION_CARDBANK_H_

#include <vector>

#include <card.h>

namespace domonion {

class CardBank {
public:
  CardBank();
  virtual ~CardBank();

  std::vector<Card*>* Selection() const;
private:
  std::vector<Card*> all_cards_;
  std::vector<Card*> selected_cards_;

  void InitializeAllCards();

  CardBank(const CardBank& other);
  CardBank& operator=(const CardBank& other);
};

} /* namespace domonion */
#endif /* DOMONION_CARDBANK_H_ */
