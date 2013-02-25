#include <vector>

#include <gamestate.h>
#include <playercollection.h>

GameState::GameState(std::vector<Player*> *players,
    std::vector<SupplyPile*> *supply_piles) :
    players_(players),
    supply_piles_(supply_piles) { }

GameState::~GameState() {
  for (std::vector<SupplyPile*>::const_iterator it = supply_piles_->begin();
      it != supply_piles_->end();
      ++it) {
    delete *it;
  }
  supply_piles_->clear();
  delete supply_piles_;
}

SimpleDeck& GameState::CurrentDeck() const {
  return CurrentPlayer().deck();
}

const Player& GameState::CurrentPlayer() const {
  return players_.current();
}

const PlayerCollection& GameState::players() const {
  return players_;
}

const std::vector<SupplyPile*>& GameState::supply_piles() const {
  return *supply_piles_;
}

std::vector<IViewable*>* GameState::supply_piles_viewable() const {
  std::vector<IViewable*> *result = new std::vector<IViewable*>;

  for (std::vector<SupplyPile*>::const_iterator it = supply_piles_->begin();
      it != supply_piles_->end();
      ++it) {
    result->push_back(*it);
  }

  return result;
}
