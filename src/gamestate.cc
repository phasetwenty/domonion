#include <algorithm>
#include <vector>

#include <cards/basictreasure.h>
#include <cards/basicvictory.h>
#include <gamestate.h>
#include <playercollection.h>

GameState::GameState(int player_count) :
  current_phase_(kUndefined), empty_piles_(0), players_(player_count), supply_piles_() {
  InitializeBaseSupply();

  for (std::vector<Player*>::const_iterator it = players_.players().begin();
    it != players_.players().end(); ++it) {
    StartDeck((*it)->deck());
    (*it)->deck().CleanupAndDraw();
  }
}

GameState::~GameState() {
  for (std::vector<SupplyPile*>::const_iterator it = supply_piles_.begin();
    it != supply_piles_.end(); ++it) {
    delete *it;
  }
}

bool GameState::Buy(std::string name) {
  bool result = false;
  if (is_ended()) {
    return result;
  }

  if (current_player().buys() > 0) {
    SupplyPile *pile = FindSupplyPile(name);
    if (current_player().coin() >= pile->card()->cost()) {
      result = pile->BuyOrGain();
      if (result) {
        current_player().SpendBuy();
        current_player().SpendCoin(pile->card()->cost());
        current_player().deck().Gain(pile->card());

        if (pile->count() == 0) {
          empty_piles_++;
        }

        ChangePhase();
      }
    }
  }
  return result;
}

void GameState::ChangePhase() {
  if (is_ended()) {
    return;
  }

  if (current_phase_ == kUndefined) {
    current_phase_ = kAction;
  }

  switch (current_phase_) {
  case kUndefined: {
    // Won't happen, but I don't like warnings.
    break;
  }
  case kAction: {
    if (current_player().actions() == 0 || !current_deck().hand_has_actions()) {
      current_phase_ = kBuy;
    }
    break;
  }
  case kBuy: {
    if (current_player().buys() == 0) {
      /*
       * I don't approve of this setup in the long run as it skips any
       * opportunity for UI updates.
       */
      current_phase_ = kCleanupDiscard;
      current_deck().CleanupAndDraw();
      current_phase_ = kUndefined;
      NextTurn();
    }
    break;
  }
  case kCleanupDiscard: {
    // Won't happen, but I don't like warnings.
    break;
  }
  }
}

SupplyPile* GameState::FindSupplyPile(std::string name) const {
  SupplyPile *result;
  for (std::vector<SupplyPile*>::const_iterator it = supply_piles_.begin();
    it != supply_piles_.end(); ++it) {
    if (name == (*it)->name()) {
      result = *it;
      break;
    }
  }

  return result;
}

void GameState::InitializeBaseSupply() {
  supply_piles_.push_back(new SupplyPile(
    new BasicVictory("Estate", 1, 2, 24, ")1(")));
  supply_piles_.push_back(new SupplyPile(
    new BasicVictory("Duchy", 3, 5, 12, ")3(")));
  supply_piles_.push_back(new SupplyPile(
    new BasicVictory("Province", 6, 8, 12, ")6(")));

  supply_piles_.push_back(new SupplyPile(
    new BasicTreasure("Copper", 1, 0, 60, "(1)")));
  supply_piles_.push_back(new SupplyPile(
    new BasicTreasure("Silver", 2, 3, 60, "(2)")));
  supply_piles_.push_back(new SupplyPile(
    new BasicTreasure("Gold", 3, 6, 60, "(3)")));
}

void GameState::NextTurn() {
  if (!is_ended()) {
    current_player().EndTurn();
    players_.Advance();
    current_player().StartTurn();

    ChangePhase();
  }
}

void GameState::PlayCard(const Card& card) {
  if (card.is_playable(*this) && !is_ended()) {
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

GameState::Phases GameState::current_phase() const {
  return current_phase_;
}

Player& GameState::current_player() const {
  return players_.current();
}

bool GameState::is_ended() const {
  SupplyPile *provinces = FindSupplyPile("Province");
  return provinces->count() == 0 || empty_piles_ >= 1;
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
    it != supply_piles_.end(); ++it) {
    result->push_back(*it);
  }

  return result;
}
