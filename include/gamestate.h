#ifndef DOMONION_GAMESTATE_H
#define DOMONION_GAMESTATE_H

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
  enum Phases { kUndefined = 0, kAction, kBuy, kCleanupDiscard };

  GameState(int player_count);
  ~GameState();

  bool Buy(std::string name);
  void NextTurn();
  void PlayCard(const Card& card);
  void Start();

  Deck& current_deck() const;
  Phases current_phase() const;
  Player& current_player() const;
  const std::vector<Player*>& players() const;
  const std::vector<SupplyPile*>& supply_piles() const;
  std::vector<const IViewable*>* supply_piles_viewable() const;
private:
  Phases current_phase_;
  PlayerCollection players_;
  std::vector<SupplyPile*> supply_piles_;

  GameState();
  GameState(const GameState& other);

  /*
   * This is handy during development, but may not be appropriate in the final
   * product.
   */
  void ChangePhase();
  SupplyPile* FindSupplyPile(std::string name);
  void InitializeBaseSupply();
  void StartDeck(Deck& deck);

  GameState& operator=(const GameState& other);
};

#endif // DOMONION_GAMESTATE_H
