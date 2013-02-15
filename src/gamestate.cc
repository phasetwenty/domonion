#include <vector>

#include <gamestate.h>
#include <playercollection.h>

GameState::GameState(std::vector<Player>& players,
    std::vector<SupplyPile*> *supply_piles) : supply_piles_(supply_piles) {
  players_ = new PlayerCollection(players);
}

GameState::~GameState() { }

const Player& GameState::CurrentPlayer() const {
  return players_->current();
}

const PlayerCollection* GameState::players() const {
  return players_;
}

const std::vector<SupplyPile*>& GameState::supply_piles() const {
  return *supply_piles_;
}

const std::vector<IViewable*>* GameState::supply_piles_viewable() const {
  std::vector<IViewable*> *result = new std::vector<IViewable*>;

  for (std::vector<SupplyPile*>::iterator it = supply_piles_->begin();
      it != supply_piles_->end();
      ++it) {
    result->push_back(&(**it));
  }

  return result;
}
