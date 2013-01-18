#include <supplypile.h>

SupplyPile::SupplyPile(Card& card) {

}

SupplyPile::SupplyPile(const SupplyPile& other) {

}

SupplyPile::~SupplyPile() {

}

SupplyPile& SupplyPile::operator=(const SupplyPile& other) {
  return *this;
}

bool SupplyPile::operator==(const SupplyPile& other) const {
  return false;
  ///TODO: return ...;
}

