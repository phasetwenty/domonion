#include <algorithm>
#include <vector>

#include <gamestate.h>
#include <playercollection.h>

GameState::GameState(int player_count, std::vector<SupplyPile*> *supply_piles) :
    players_(player_count), supply_piles_(supply_piles) {
  for (std::vector<Player*>::const_iterator it = players_.players().begin();
      it != players_.players().end();
      ++it) {
    StartDeck((*it)->deck());
  }
}

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

  bool result = false;
  if (current_player().coin() >= pile->card()->cost()) {
    result = pile->BuyOrGain();
    if (result) {
      current_player().SpendCoin(pile->card()->cost());
      current_player().deck().Gain(pile->card());
    }
  }
  return result;
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

void GameState::StartDeck(Deck& deck) {
  SupplyPile *estate_pile = FindSupplyPile("Estate");
  SupplyPile *copper_pile = FindSupplyPile("Copper");

  for (int i = 0; i < 3; ++i) {
    estate_pile->BuyOrGain();
    deck.Gain(estate_pile->card());
  }
  for (int i = 0; i < 7; ++i) {
    copper_pile->BuyOrGain();
    deck.Gain(copper_pile->card());
  }
}

Deck& GameState::current_deck() const {
  return current_player().deck();
}

Player& GameState::current_player() const {
  return players_.current();
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
