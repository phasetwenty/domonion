#include <algorithm>
#include <vector>

#include <cards/basictreasure.h>
#include <cards/basicvictory.h>
#include <gamestate.h>
#include <playercollection.h>

GameState::GameState(int player_count) : players_(player_count), supply_piles_() {
  InitializeBaseSupply();

  for (std::vector<Player*>::const_iterator it = players_.players().begin();
      it != players_.players().end();
      ++it) {
    StartDeck((*it)->deck());
    (*it)->deck().CleanupAndDraw();
  }
}

GameState::~GameState() {
  for (std::vector<SupplyPile*>::const_iterator it = supply_piles_.begin();
      it != supply_piles_.end();
      ++it) {
    delete *it;
  }
}

bool GameState::Buy(std::string name) {
  bool result = false;
  if (current_player().buys() > 0) {
    SupplyPile *pile = FindSupplyPile(name);
    if (current_player().coin() >= pile->card()->cost()) {
      result = pile->BuyOrGain();
      if (result) {
        current_player().SpendBuy();
        current_player().SpendCoin(pile->card()->cost());
        current_player().deck().Gain(pile->card());
        ChangePhase();
      }
    }
  }
  return result;
}

void GameState::ChangePhase() {
  switch (current_phase()) {
  case Player::kUndefined: {
    current_player().set_phase(Player::kAction);
    if (current_player().actions() == 0 || !current_deck().hand_has_actions()) {
      current_player().set_phase(Player::kBuy);
    }
    break;
  } case Player::kAction: {
    if (current_player().actions() == 0 || !current_deck().hand_has_actions()) {
      current_player().set_phase(Player::kBuy);
    }
    break;
  } case Player::kBuy: {
    if (current_player().buys() == 0) {
      /*
       * I don't approve of this setup in the long run as it skips any
       * opportunity for UI updates.
       */
      current_player().set_phase(Player::kCleanupDiscard);
      current_deck().CleanupAndDraw();
      current_player().set_phase(Player::kUndefined);
      NextTurn();
    }
    break;
  }
  }
  // TODO: do they enter the cleanup/discard phase? take action based on it?
}

SupplyPile* GameState::FindSupplyPile(std::string name) {
  SupplyPile *result;
  for (std::vector<SupplyPile*>::iterator it = supply_piles_.begin();
      it != supply_piles_.end();
      ++it) {
    if (name == (*it)->name()) {
      result = *it;
      break;
    }
  }

  return result;
}

void GameState::InitializeBaseSupply() {
  supply_piles_.push_back(new SupplyPile(
    new BasicVictory("Estate", 2, 24, ")1(")));
  supply_piles_.push_back(new SupplyPile(
    new BasicVictory("Duchy", 5, 12, ")3(")));
  supply_piles_.push_back(new SupplyPile(
    new BasicVictory("Province", 8, 12, ")6(")));

  supply_piles_.push_back(new SupplyPile(
    new BasicTreasure("Copper", 1, 0, 60, "(1)")));
  supply_piles_.push_back(new SupplyPile(
    new BasicTreasure("Silver", 2, 3, 60, "(2)")));
  supply_piles_.push_back(new SupplyPile(
    new BasicTreasure("Gold", 3, 6, 60, "(3)")));

}

void GameState::NextTurn() {
  current_player().EndTurn();
  players_.Advance();
  current_player().StartTurn();

}

void GameState::PlayCard(const Card& card) {
  if (card.is_playable(*this)) {
    current_deck().Play(card);
    card.Play(*this);

    ChangePhase();
  }
}

void GameState::Start() {
  current_player().StartTurn();
  ChangePhase();
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

Player::Phases GameState::current_phase() const {
  return current_player().phase();
}

Player& GameState::current_player() const {
  return players_.current();
}

const std::vector<Player*>& GameState::players() const {
  return players_.players();
}

const std::vector<SupplyPile*>& GameState::supply_piles() const {
  return supply_piles_;
}

std::vector<const IViewable*>* GameState::supply_piles_viewable() const {
  std::vector<const IViewable*> *result = new std::vector<const IViewable*>;

  for (std::vector<SupplyPile*>::const_iterator it = supply_piles_.begin();
      it != supply_piles_.end();
      ++it) {
    result->push_back(*it);
  }

  return result;
}
