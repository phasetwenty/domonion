/*
 * basictreasure.h
 *
 *  Created on: Oct 10, 2012
 *      Author: chris
 */

#ifndef DOMONION_BASICTREASURE_H_
#define DOMONION_BASICTREASURE_H_

class BasicTreasure : public Card {
public:
  BasicTreasure(std::string name, int coins_provided, int cost,
                std::string text, std::string type);
  virtual ~BasicTreasure();

  int coin_provided() const;
private:
  int coin_provided_;
};

#endif /* DOMONION_BASICTREASURE_H_ */
