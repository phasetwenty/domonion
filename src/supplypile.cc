#include <supplypile.h>

SupplyPile::SupplyPile(const Card& card, int initial_count) : card_(card) {
  count_ = initial_count;
}

SupplyPile::SupplyPile(const SupplyPile& other) : card_(other.card()) {
  count_ = other.count();
}

SupplyPile::~SupplyPile() {

}

bool SupplyPile::operator==(const SupplyPile& other) const {
  return false;
}

const Card& SupplyPile::card() const {
  return card_;
}

int SupplyPile::count() const {
  return count_;
}
