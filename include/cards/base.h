/*
 * base.h
 *
 *  Created on: Mar 13, 2013
 *      Author: chris
 */

#ifndef DOMONION_CARDS_BASE_H_
#define DOMONION_CARDS_BASE_H_

#include <card.h>

namespace domonion {

class GameState;

namespace cards {

class IPointsProvider {
public:
  virtual ~IPointsProvider() { }

  virtual int points_provided(const GameState& game) const = 0;
};

class Curse : public Card, public IPointsProvider {
public:
  Curse();
  ~Curse() { }

  virtual void Play(GameState& game) const { }

  virtual int points_provided(const GameState& game) const;
private:
  Curse(const Curse& other);
  Curse& operator=(const Curse& other);
};

class ITreasure {
public:
  virtual ~ITreasure() { }

  virtual int coin_provided(const GameState& game) const = 0;
protected:
  ITreasure() { }
};

class BasicTreasure : public Card, public ITreasure {
public:
  BasicTreasure(std::string name,
    int coins_provided,
    int cost,
    int initial_supply,
    std::string text);
  virtual ~BasicTreasure() { }

  virtual void Play(GameState& game) const;

  virtual int coin_provided(const GameState& game) const;
private:
  int coin_provided_;

  BasicTreasure();
  BasicTreasure(const BasicTreasure& other);

  BasicTreasure& operator=(const BasicTreasure& other);
};

class BasicVictory: public Card, public IPointsProvider {
public:
  BasicVictory(std::string name,
    int points_provided,
    int cost,
    int initial_supply,
    std::string text);
  virtual ~BasicVictory() { }

  virtual void Play(domonion::GameState& game) const { }

  int points_provided(const GameState& game) const;
private:
  int victory_points_;

  BasicVictory();
  BasicVictory(const BasicVictory& other);
  BasicVictory& operator=(const BasicVictory& other);
};

}
}


#endif /* DOMONION_CARDS_BASE_H_ */
