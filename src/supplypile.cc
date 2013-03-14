#include <sstream>

#include <gamestate.h>
#include <supplypile.h>

namespace domonion {

SupplyPile::SupplyPile(const Card *card, const GameState& game) :
  card_(card), count_(card->initial_supply(game.players().size())), game_(game) { }

SupplyPile::~SupplyPile() {
  delete card_;
}

bool SupplyPile::operator==(const SupplyPile& other) const {
  return false;
}

bool SupplyPile::BuyOrGain() {
  bool result = (count_ > 0);
  if (result) {
    count_--;
  }
  return result;
}

std::string* SupplyPile::Info() const {
  return card()->Info();
}

std::string* SupplyPile::ToString() const {
  std::stringstream ss;
  std::string *name = card()->ToString();
  ss << card()->cost(game_) << " " << std::string(*name) << " (" << count() << ")";

  delete name;
  return new std::string(ss.str());
}

const Card* SupplyPile::card() const {
  return card_;
}

int SupplyPile::count() const {
  return count_;
}

const std::string& SupplyPile::name() const {
  return card_->name();
}

}
