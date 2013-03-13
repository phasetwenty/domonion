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

/*
 * Whereas Card and card implementations hold the specifics for each card,
 * CardBank Holds the game-wide logic for cards and card instantiation.
 */
class CardBank {
public:
  CardBank(int player_count);
  virtual ~CardBank() { }

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
  static const int kInitialCopperCount = 60;
  static const int kInitialSilverCount = 40;
  static const int kInitialGoldCount = 30;
  static const int kMaxEstateCount = 24;
  static const int kMaxDuchyCount = 12;
  static const int kMaxProvinceCount = 12;

  std::vector<Card*> all_cards_;
  std::vector<Card*> selected_cards_;

  Card *copper_;
  Card *silver_;
  Card *gold_;

  Card *estate_;
  Card *duchy_;
  Card *province_;
  Card *curse_;

  CardBank();
  CardBank(const CardBank& other);

  void InitializeAllCards(int player_count);

  int initial_estates(int player_count) const;
  int initial_duchies(int player_count) const;
  int initial_provinces(int player_count) const;


  CardBank& operator=(const CardBank& other);
};

} /* namespace domonion */
#endif /* DOMONION_CARDBANK_H_ */
