#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <vector>

#include <playercollection.h>
#include <supplypile.h>

class Player;
class Deck;

/*
 * GameState
 * All of the state of the game in progress.
 */
class GameState {
public:
  GameState(std::vector<Player*> *players, std::vector<SupplyPile*> *supply_piles);
  ~GameState();

  bool Buy(std::string name);
  /*
   * This is handy during development, but may not be appropriate in the final
   * product.
   */
  SupplyPile* FindSupplyPile(std::string name);

  Deck& current_deck() const;
  const Player& current_player() const;
  const std::vector<Player*>& players() const;
  const std::vector<SupplyPile*>& supply_piles() const;
  std::vector<const IViewable*>* supply_piles_viewable() const;
private:
  /*
   * Card bank? Some object that handles the collection of Supply piles for
   * all cards that need to be out. It would be inappropriate for the game
   * state to have to track all that information on its own.
   */
  PlayerCollection players_;
  std::vector<SupplyPile*> *supply_piles_;

  GameState();
  GameState(const GameState& other);
  GameState& operator=(const GameState& other);
};

#endif // GAMESTATE_H

/*
 * Things tracked in the game state (directly or indirectly):
 * Players
 * Supply piles
 * * How to optionally include supplies: Colony, Platinum
 * Turns
 * The state of the current turn
 * * Whose turn it is
 * * Actions/Treasures in play / tableau
 * * Actions/Buy/Coin count
 */
