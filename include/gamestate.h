#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <vector>

#include <player.h>
#include <playercollection.h>
#include <supplypile.h>

class Deck;

/*
 * GameState
 * All of the state of the game in progress.
 */

class GameState {
public:
  GameState(int player_count);
  ~GameState();

  bool Buy(std::string name);
  void NextTurn();
  void Start();

  Deck& current_deck() const;
  Phases current_phase() const;
  Player& current_player() const;
  const std::vector<Player*>& players() const;
  const std::vector<SupplyPile*>& supply_piles() const;
  std::vector<const IViewable*>* supply_piles_viewable() const;
private:
  PlayerCollection players_;
  std::vector<SupplyPile*> supply_piles_;

  GameState();
  GameState(const GameState& other);

  /*
   * This is handy during development, but may not be appropriate in the final
   * product.
   */
  SupplyPile* FindSupplyPile(std::string name);
  void InitializeBaseSupply();
  void StartDeck(Deck& deck);

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
