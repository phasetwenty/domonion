#include <sstream>

#include <supplypile.h>

domonion::SupplyPile::SupplyPile(domonion::Card *card) :
  card_(card), count_(card->initial_supply()) { }

domonion::SupplyPile::~SupplyPile() {
  delete card_;
}

bool domonion::SupplyPile::operator==(const domonion::SupplyPile& other) const {
  return false;
}

bool domonion::SupplyPile::BuyOrGain() {
  bool result = (count_ > 0);
  if (result) {
    count_--;
  }
  return result;
}

std::string* domonion::SupplyPile::Info() const {
  return card()->Info();
}

std::string* domonion::SupplyPile::ToString() const {
  std::stringstream ss;
  ss << "(" << count() << ") " << card()->name() ;
  return new std::string(ss.str());
}

const domonion::Card* domonion::SupplyPile::card() const {
  return card_;
}

int domonion::SupplyPile::count() const {
  return count_;
}

const std::string& domonion::SupplyPile::name() const {
  return card_->name();
}
