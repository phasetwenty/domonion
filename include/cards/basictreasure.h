/*
 * basictreasure.h
 *
 *  Created on: Oct 10, 2012
 *      Author: chris
 */

#ifndef DOMONION_BASICTREASURE_H_
#define DOMONION_BASICTREASURE_H_

#include <card.h>

class BasicTreasure: public Card {
public:
  BasicTreasure(std::string name,
    int coins_provided,
    int cost,
    int initial_supply,
    std::string text);
  virtual ~BasicTreasure();

  virtual void Play(GameState& game) const;

  int coin_provided() const;
  bool is_playable(const GameState& game) const;
private:
  int coin_provided_;

  BasicTreasure();
  BasicTreasure(const BasicTreasure& other);

  BasicTreasure& operator=(const BasicTreasure& other);
};

#endif /* DOMONION_BASICTREASURE_H_ */

/*
 * Remember: treasures initial supply depends on the type.
 */
