/*
 * BasicVictory.h
 *
 *  Created on: Oct 28, 2012
 *      Author: chris
 */

#ifndef DOMONION_CARDS_BASICVICTORY_H_
#define DOMONION_CARDS_BASICVICTORY_H_

#include <card.h>

namespace domonion {
namespace cards {

class BasicVictory: public Card {
public:
  BasicVictory(std::string name,
    int points_provided,
    int cost,
    int initial_supply,
    std::string text);
  virtual ~BasicVictory();

  virtual void Play(domonion::GameState& game) const;

  virtual bool is_playable() const;
  int points_provided() const;
private:
  int victory_points_;

  BasicVictory();
  BasicVictory(const BasicVictory& other);
  BasicVictory& operator=(const BasicVictory& other);
};

}
}

#endif /* DOMONION_BASICVICTORY_H_ */
