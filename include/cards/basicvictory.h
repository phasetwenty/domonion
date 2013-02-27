/*
 * BasicVictory.h
 *
 *  Created on: Oct 28, 2012
 *      Author: chris
 */

#ifndef DOMONION_BASICVICTORY_H_
#define DOMONION_BASICVICTORY_H_

#include <card.h>

class BasicVictory: public Card {
public:
  BasicVictory(std::string name,
    int cost,
    int initial_supply,
    std::string text);
  virtual ~BasicVictory();

private:
  BasicVictory();
  BasicVictory(const BasicVictory& other);
  BasicVictory& operator=(const BasicVictory& other);
};

#endif /* DOMONION_BASICVICTORY_H_ */
