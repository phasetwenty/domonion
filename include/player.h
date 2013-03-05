#ifndef DOMONION_PLAYER_H
#define DOMONION_PLAYER_H

#include <string>

#include <deck.h>

class Player {
public:
  Player(std::string name, Deck *deck);
  ~Player();

  /*
   * Adds `c` to the amount of coin this player has. Returns the new amount.
   */
  int AddCoin(int c);
  void EndTurn();
  int SpendCoin(int c);
  void StartTurn();
  int SpendBuy();

  int actions() const;
  int buys() const;
  int coin() const;
  Deck& deck() const;
  const std::string& name() const;
  int victory_points() const;

private:
  int actions_;
  int buys_;
  int coin_;
  Deck *deck_;
  std::string name_;

  Player();
  Player(const Player& other);
  Player& operator=(const Player& other);
};

#endif // DOMONION_PLAYER_H
