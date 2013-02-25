#include <sstream>

#include <supplypile.h>

SupplyPile::SupplyPile(Card *card, int initial_count) :
  card_(card), count_(initial_count) { }

SupplyPile::~SupplyPile() {
  delete card_;
}

bool SupplyPile::operator==(const SupplyPile& other) const {
  return false;
}

bool SupplyPile::BuyOrGain() {
  bool result = (count_ == 0);
  if (count_ > 0) {
    count_--;
  }
  return result;
}

std::string* SupplyPile::Info() const {
  return card().Info();
}

std::string* SupplyPile::ToString() const {
  std::stringstream ss;
  ss << card().name() << " (" << count() << ")";
  return new std::string(ss.str());
}

const Card& SupplyPile::card() const {
  return *card_;
}

int SupplyPile::count() const {
  return count_;
}

const std::string& SupplyPile::name() const {
  return card_->name();
}
