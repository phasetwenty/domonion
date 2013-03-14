#ifndef DOMONION_GAMESTATE_H
#define DOMONION_GAMESTATE_H

#include <vector>

#include <player.h>
#include <playercollection.h>
#include <supplypile.h>

namespace domonion {

class CardBank;
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
  /*
   * This is handy during development, but may not be appropriate in the final
   * product.
   */
  void AddToSupply(Card *card);
  void ChangePhase(bool force);
  SupplyPile* FindSupplyPile(std::string name) const;
  /*
   * TODO: Reexamine.
   * I don't know that I like this logic. I can create a game but in order for
   * it to run, this method must be called by the user.
   */
  void InitializeBaseSupply(const CardBank& bank);
  const Player& NextPlayer();
  void NextTurn();
  void PlayCard(const Card& card);
  void Start();

  Deck& current_deck() const;
  Phases current_phase() const;
  Player& current_player() const;
  bool is_ended() const;
  const std::vector<Player*>& players() const;
  const std::vector<SupplyPile*>& supply_piles() const;
  std::vector<const IViewable*>* supply_piles_viewable() const;
private:
  Phases current_phase_;
  int empty_piles_;
  PlayerCollection players_;
  std::vector<SupplyPile*> supply_piles_;

  GameState();
  GameState(const GameState& other);

  bool IsCardPlayable(const Card& card) const;
  void StartDeck(Deck& deck);

  GameState& operator=(const GameState& other);
};

}

#endif // DOMONION_GAMESTATE_H
