#ifndef DOMONION_PLAYER_H
#define DOMONION_PLAYER_H

#include <string>

#include <deck.h>

class Player {
public:
  enum Phases { kUndefined = 0, kAction, kBuy, kCleanupDiscard };

  Player(Deck *deck);
  ~Player();

  /*
   * Adds `c` to the amount of coin this player has. Returns the new amount.
   */
  int AddCoin(int c);
  void EndTurn();
  int SpendCoin(int c);
  void StartTurn();

  int actions() const;
  int buys() const;
  int coin() const;
  Deck& deck() const;
  Phases phase() const;
  void set_phase(Phases value);

private:
  std::string name_;

  int actions_;
  int buys_;
  int coin_;
  Deck *deck_;
  Phases phase_;

  Player();
  Player(const Player& other);
  Player& operator=(const Player& other);
};

#endif // DOMONION_PLAYER_H
/*
 * Things to track
 * * Deck
 * * Victory token count (Prosperity and beyond)
 * * Hand
 * * Tableau: belongs to GameState or Player? I think GameState because there
 *   can only be one at a time.
 */
