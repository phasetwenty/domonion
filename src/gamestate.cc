#include <algorithm>
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

bool GameState::Buy(std::string name) {
  SupplyPile *pile = FindSupplyPile(name);

  bool result = pile->BuyOrGain();
  if (result) {
    CurrentPlayer().deck().Gain(pile->card());
  }

  return result;
}

Deck& GameState::CurrentDeck() const {
  return CurrentPlayer().deck();
}

const Player& GameState::CurrentPlayer() const {
  return players_.current();
}

SupplyPile* GameState::FindSupplyPile(std::string name) {
  SupplyPile *result;
  for (std::vector<SupplyPile*>::iterator it = supply_piles_->begin();
      it != supply_piles_->end();
      ++it) {
    if (name == (*it)->name()) {
      result = *it;
      break;
    }
  }

  return result;
}

const std::vector<Player*>& GameState::players() const {
  return players_.players();
}

const std::vector<SupplyPile*>& GameState::supply_piles() const {
  return *supply_piles_;
}

std::vector<const IViewable*>* GameState::supply_piles_viewable() const {
  std::vector<const IViewable*> *result = new std::vector<const IViewable*>;

  for (std::vector<SupplyPile*>::const_iterator it = supply_piles_->begin();
      it != supply_piles_->end();
      ++it) {
    result->push_back(*it);
  }

  return result;
}
