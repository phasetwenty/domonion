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

  /*
   * CardBank creates these cards, but they will be owned by the user.
   */
  const Card* copper() const;
  const Card* silver() const;
  const Card* gold() const;
  const Card* estate() const;
  const Card* duchy() const;
  const Card* province() const;
  const Card* curse() const;
private:
  std::vector<Card*> all_cards_;
  std::vector<Card*> selected_cards_;

  Card *copper_;
  Card *silver_;
  Card *gold_;

  Card *estate_;
  Card *duchy_;
  Card *province_;
  Card *curse_;

  void InitializeAllCards();

  CardBank(const CardBank& other);
  CardBank& operator=(const CardBank& other);
};

} /* namespace domonion */
#endif /* DOMONION_CARDBANK_H_ */
